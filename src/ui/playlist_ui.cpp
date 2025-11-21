#include "ui/Main.hpp"
#include "ui/playlist_ui.hpp"
#include "ui/song_ui.hpp"
#include <iostream>

void PlaylistUI::run()
{
    bool running = true;

    Main::clearScreen();
    drawPlaylistPage();

    while (running)
    {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty())
        {
            processCommand(input, running);
            if (running)
            {
                Main::clearScreen();
                drawPlaylistPage();
            }
        }
    }
}

void PlaylistUI::drawPlaylistPage()
{
    Main::player_->drawPlayerHeader();
    std::cout << std::endl;
    std::cout << "Playlist " << currentPlaylist_->name << std::endl;
    int index = 1;
    node<Song> *current = currentPlaylist_->songs.head();
    node<Song> *start = current;

    while (current)
    {
        std::cout << index++ << ". " << current->data.title << " by " << current->data.artist << std::endl;
        current = currentPlaylist_->songs.next(current);

        // Stop if we've looped back to the start or reached the end
        if (current == start || current == nullptr)
            break;
    }
    std::cout << std::endl;
    std::cout << "-2. play" << std::endl;
    std::cout << "-1. delete a song" << std::endl;
    std::cout << "0. back" << std::endl;
    std::cout << std::endl;
    std::cout << ">. next " << std::endl;
    std::cout << ">. prev " << std::endl;
}

void PlaylistUI::processCommand(const std::string &command, bool &running)
{
    if (command == "next")
    {
        Main::player_->next();
        Main::checkAndPopFinishedPlayer(); // Check if finished after next
    }
    else if (command == "prev")
    {
        Main::player_->prev();
        Main::checkAndPopFinishedPlayer(); // Check if finished after prev
    }
    else if (std::isdigit(command[0]) || (command[0] == '-' && command.size() > 1 && std::isdigit(command[1])))
    {
        int songIndex = std::stoi(command);
        if (songIndex == 0)
        {
            running = false;
        }
        else if (songIndex == -1)
        {
            std::cout << "Which song: ";
            std::string songNumberStr;
            std::getline(std::cin, songNumberStr);
            try
            {
                songIndex = std::stoi(songNumberStr);
                deleteSong(songIndex - 1);
            }
            catch (...)
            {
                std::cout << "Invalid song number" << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }
        }
        else if (songIndex == -2)
        {
            // Check if this playlist is already playing
            if (Main::isPlaylistCurrentlyPlaying(currentPlaylist_))
            {
                std::cout << "This playlist is already being played!" << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }

            std::cout << "Enter starting song number: ";
            std::string songNumberStr;
            std::getline(std::cin, songNumberStr);
            int startIndex;
            try
            {
                startIndex = std::stoi(songNumberStr);

                if (Main::player_->getSource() != PlayerSource::NONE)
                {
                    Main::player_->next();
                }

                // load songs into cdll starting from startIndex - 1
                if (startIndex < 1)
                    Main::pushPlayer(new PlaylistPlayer(currentPlaylist_, 0));
                else if (startIndex > static_cast<int>(currentPlaylist_->songs.size()))
                    Main::pushPlayer(new PlaylistPlayer(currentPlaylist_, static_cast<int>(currentPlaylist_->songs.size()) - 1));
                else
                    Main::pushPlayer(new PlaylistPlayer(currentPlaylist_, startIndex - 1));
            }
            catch (...)
            {
                std::cout << "Invalid input" << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }
        }
        else if (songIndex > 0 && songIndex <= currentPlaylist_->songs.size())
        {
            node<Song> *songNode = currentPlaylist_->songs.getAt(songIndex - 1);
            if (songNode)
            {
                SongUI songUI(&songNode->data);
                songUI.run();
            }
        }
        else
        {
            std::cout << "Invalid song number" << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
    else
    {
        std::cout << "unknown command" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
}

void PlaylistUI::deleteSong(int index)
{
    if (index >= 0 && index < currentPlaylist_->songs.size())
    {
        node<Song> *nodeToDelete = currentPlaylist_->songs.getAt(index);
        if (nodeToDelete)
        {
            Song songToDelete = nodeToDelete->data;

            // Move currentSong_ in any PlaylistPlayer that's pointing to this node
            movePlayersAwayFromNode(nodeToDelete);

            currentPlaylist_->songs.remove(nodeToDelete);
            std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
        }
    }
    // delete first song
    else if (index < 0)
    {
        node<Song> *nodeToDelete = currentPlaylist_->songs.head();
        if (nodeToDelete)
        {
            Song songToDelete = nodeToDelete->data;

            // Move currentSong_ in any PlaylistPlayer that's pointing to this node
            movePlayersAwayFromNode(nodeToDelete);

            currentPlaylist_->songs.remove(nodeToDelete);
            std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
        }
    }
    // delete last song
    else if (index >= currentPlaylist_->songs.size())
    {
        node<Song> *nodeToDelete = currentPlaylist_->songs.tail();
        if (nodeToDelete)
        {
            Song songToDelete = nodeToDelete->data;

            // Move currentSong_ in any PlaylistPlayer that's pointing to this node
            movePlayersAwayFromNode(nodeToDelete);

            currentPlaylist_->songs.remove(nodeToDelete);
            std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid song index" << std::endl;
    }
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void PlaylistUI::movePlayersAwayFromNode(node<Song> *nodeToDelete)
{
    // Move current player if it's pointing to this node
    if (Main::player_ && Main::player_->getPlaylist() == currentPlaylist_)
    {
        PlaylistPlayer *playlistPlayer = dynamic_cast<PlaylistPlayer *>(Main::player_);
        if (playlistPlayer)
        {
            playlistPlayer->moveCurrentSongIfMatches(nodeToDelete);
        }
    }

    // Move all players in the stack if they're pointing to this node
    std::stack<Player *> tempStack;

    while (!Main::playersStack_.empty())
    {
        Player *p = Main::playersStack_.top();
        Main::playersStack_.pop();

        if (p->getPlaylist() == currentPlaylist_)
        {
            PlaylistPlayer *playlistPlayer = dynamic_cast<PlaylistPlayer *>(p);
            if (playlistPlayer)
            {
                playlistPlayer->moveCurrentSongIfMatches(nodeToDelete);
            }
        }

        tempStack.push(p);
    }

    // Rebuild the stack
    while (!tempStack.empty())
    {
        Main::playersStack_.push(tempStack.top());
        tempStack.pop();
    }
}
