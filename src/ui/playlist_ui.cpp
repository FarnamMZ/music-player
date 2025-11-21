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
    for (const auto &song : currentPlaylist_->songs)
    {
        std::cout << index++ << ". " << song.title << " by " << song.artist << std::endl;
    }
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
        else if (songIndex > 0 && songIndex <= static_cast<int>(currentPlaylist_->songs.size()))
        {
            SongUI songUI(&currentPlaylist_->songs[songIndex - 1]);
            songUI.run();
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
    if (index >= 0 && index < static_cast<int>(currentPlaylist_->songs.size()))
    {
        Song songToDelete = currentPlaylist_->songs[index];
        currentPlaylist_->songs.erase(currentPlaylist_->songs.begin() + index);
        std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
    }
    // delete first song
    else if (index < 0)
    {
        Song songToDelete = currentPlaylist_->songs[0];
        currentPlaylist_->songs.erase(currentPlaylist_->songs.begin());
        std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
    }
    // delete last song
    else if (index >= static_cast<int>(currentPlaylist_->songs.size()))
    {
        Song songToDelete = currentPlaylist_->songs.back();
        currentPlaylist_->songs.pop_back();
        std::cout << "Deleted \"" << songToDelete.title << "\" from playlist \"" << currentPlaylist_->name << "\"" << std::endl;
    }
    else
    {
        std::cout << "Invalid song index" << std::endl;
    }
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}
