#include "ui/song_ui.hpp"
#include "ui/Main.hpp"
#include <iostream>

void SongUI::run()
{
  bool running = true;

  Main::clearScreen();
  std::cout << currentSong_.title << " - " << currentSong_.artist << std::endl;
  drawSongPage();

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
        std::cout << currentSong_.title << " - " << currentSong_.artist << std::endl;
        drawSongPage();
      }
    }
  }
}

void SongUI::processCommand(const std::string &command, bool &running)
{
  if (command == "1")
  {
    Main::clearScreen();

    // Show list of playlists containing this song
    drawPlaylistsContainingSong();
  }
  else if (command == "2")
  {
    drawExistedPlaylists();

    // get playlist name from user
    std::cout << "\nEnter playlist name to add the song to: ";
    std::string playlistName;
    std::getline(std::cin, playlistName);

    // check if song already exists in the playlist
    try {
      if (Main::songExistsInPlaylist(currentSong_, playlistName))
      {
        std::cout << "Song already exists in the playlist \"" << playlistName << "\"." << std::endl;
        
        // wait for user to press enter
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return;
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
      
      // wait for user to press enter
      std::cout << "\nPress Enter to continue...";
      std::cin.get();
      return;
    }
    
    // get position in playlist
    try {
      drawSongsInPlaylist(playlistName);
      std::cout << "\nEnter position to add the song at: ";
      std::string positionStr;
      std::getline(std::cin, positionStr);
      
      int position = std::stoi(positionStr);
      Main::addSongToPlaylist(currentSong_, playlistName, position);

    } catch (const std::invalid_argument &e) {
      std::cout << "Invalid position. Please enter a valid number." << std::endl;
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  
    // wait for user to press enter
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
  }
  else if (command == "3")
  {
    // Add to queue
    Main::addToQueue(currentSong_);
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
  }
  else if (command == "0")
  {
    running = false;
  }
  else
  {
    std::cout << "Unknown command" << std::endl;
  }
}

void SongUI::drawSongPage()
{
  std::cout << "1. List of playlists" << std::endl;
  std::cout << "2. Add to playlist" << std::endl;
  std::cout << "3. Add to queue" << std::endl;
  std::cout << "0. back" << std::endl;
}

void SongUI::drawPlaylistsContainingSong()
{
  auto playlists = Main::getPlaylists(currentSong_);
  std::cout << "\nPlaylists containing this song:" << std::endl;
  if (playlists.empty())
  {
    std::cout << "This song is not in any playlist." << std::endl;
  }
  else
  {
    for (const auto &playlist : playlists)
    {
      std::cout << "- " << playlist.name << std::endl;
    }
  }
  std::cout << "\nPress Enter to continue...";
  std::cin.get();
}

void SongUI::drawExistedPlaylists()
{
  auto &playlists = Main::playlists_;
  std::cout << "\nExisting playlists:" << std::endl;
  for (const auto &playlist : playlists)
  {
    std::cout << "- " << playlist.name << std::endl;
  }
}

void SongUI::drawSongsInPlaylist(const std::string &playlistName)
{
  auto &playlists = Main::playlists_;
  auto it = std::find_if(playlists.begin(), playlists.end(),
                         [&playlistName](const Playlist &pl) { return pl.name == playlistName; });
  if (it != playlists.end())
  {
    std::cout << "\nSongs in playlist '" << playlistName << "':" << std::endl;
    for (const auto &song : it->songs)
    {
      std::cout << "- " << song.title << " - " << song.artist << std::endl;
    }
  }
  else
  {
    throw std::runtime_error("Playlist \"" + playlistName + "\" not found.");
  }
}