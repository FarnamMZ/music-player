#include "ui/playlists_ui.hpp"
#include "ui/playlist_ui.hpp"
#include "ui/Main.hpp"
#include <iostream>

void PlaylistsUI::run()
{
    bool running = true;

    Main::clearScreen();
    drawPlaylistsPage();

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
                drawPlaylistsPage();
            }
        }
    }
}

void PlaylistsUI::drawPlaylistsPage()
{
    Main::player_->drawPlayerHeader();
    std::cout << std::endl;
    std::cout << "List of playlists" << std::endl;
    int index = 1;
    for (const auto &playlist : Main::playlists_)
    {
        std::cout << index++ << ". " << playlist.name << " (" << playlist.songs.size() << " songs)" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-1. add playlist" << std::endl;
    std::cout << "0. back" << std::endl;
    std::cout << std::endl;
    std::cout << ">. next " << std::endl;
    std::cout << ">. prev " << std::endl;
}

void PlaylistsUI::processCommand(const std::string &command, bool &running)
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
        int playlistIndex = std::stoi(command);
        if (playlistIndex == 0)
        {
            running = false;
        }
        else if (playlistIndex == -1)
        {
            addNewPlaylist();
        }
        else if (playlistIndex > 0 && playlistIndex <= static_cast<int>(Main::playlists_.size()))
        {
            PlaylistUI playlistUI(&Main::playlists_[playlistIndex - 1]); // Pass pointer to the playlist
            playlistUI.run();
        }
        else
        {
            std::cout << "Invalid playlist number" << std::endl;
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

bool PlaylistsUI::playlistExists(const std::string &playlistName)
{
    for (const auto &playlist : Main::playlists_)
    {
        if (playlist.name == playlistName)
        {
            return true;
        }
    }
    return false;
}

void PlaylistsUI::addNewPlaylist()
{
    std::cout << "Enter new playlist name: ";
    std::string playlistName;
    std::getline(std::cin, playlistName);

    if (playlistExists(playlistName))
    {
        std::cout << "Playlist \"" << playlistName << "\" already exists." << std::endl;
    }
    else
    {
        Main::playlists_.push_back({playlistName, {}});
        std::cout << "Playlist \"" << playlistName << "\" added." << std::endl;
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}