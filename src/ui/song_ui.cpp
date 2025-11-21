#include "ui/song_ui.hpp"
#include "ui/Main.hpp"
#include "ui/playlist_ui.hpp"
#include <iostream>
#include <algorithm>

void SongUI::run()
{
  bool running = true;

  Main::clearScreen();
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
        drawSongPage();
      }
    }
  }
}

void SongUI::processCommand(const std::string &command, bool &running)
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
  else if (command == "1")
  {
    Main::clearScreen();

    // Show list of playlists containing this song and allow selection
    auto playlists = Main::getPlaylists(*currentSong_);
    if (playlists.empty())
    {
      std::cout << "This song is not in any playlist." << std::endl;
      std::cout << "\nPress Enter to continue...";
      std::cin.get();
    }
    else
    {
      // Display numbered list
      std::cout << "Playlists containing this song:" << std::endl;
      int index = 1;
      for (const auto &playlist : playlists)
      {
        std::cout << index++ << ". " << playlist.name << std::endl;
      }
      std::cout << "0. back" << std::endl;

      // Get user selection
      std::cout << "\n> ";
      std::string input;
      std::getline(std::cin, input);

      if (!input.empty() && std::isdigit(input[0]))
      {
        int selection = std::stoi(input);
        if (selection > 0 && selection <= static_cast<int>(playlists.size()))
        {
          // Find the actual playlist in Main::playlists_ by name
          std::string selectedName = playlists[selection - 1].name;
          auto it = std::find_if(Main::playlists_.begin(), Main::playlists_.end(),
                                 [&selectedName](const Playlist &pl)
                                 { return pl.name == selectedName; });
          if (it != Main::playlists_.end())
          {
            PlaylistUI playlistUI(&(*it));
            playlistUI.run();
          }
        }
      }
    }
  }
  else if (command == "2")
  {
    drawExistedPlaylists();

    // get playlist name from user
    std::cout << "\nEnter playlist name to add the song to: ";
    std::string playlistName;
    std::getline(std::cin, playlistName);

    // check if song already exists in the playlist
    try
    {
      if (Main::songExistsInPlaylist(*currentSong_, playlistName))
      {
        std::cout << "Song already exists in the playlist \"" << playlistName << "\"." << std::endl;

        // wait for user to press enter
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return;
      }
    }
    catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;

      // wait for user to press enter
      std::cout << "\nPress Enter to continue...";
      std::cin.get();
      return;
    }

    // get position in playlist
    try
    {
      drawSongsInPlaylist(playlistName);
      std::cout << "\nEnter position to add the song at: ";
      std::string positionStr;
      std::getline(std::cin, positionStr);

      int position = std::stoi(positionStr);
      Main::addSongToPlaylist(*currentSong_, playlistName, position - 1);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Invalid position. Please enter a valid number." << std::endl;
    }
    catch (const std::exception &e)
    {
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
  Main::player_->drawPlayerHeader();
  std::cout << std::endl;
  std::cout << currentSong_->title << " - " << currentSong_->artist << std::endl;
  std::cout << std::endl;
  std::cout << "1. List of playlists" << std::endl;
  std::cout << "2. Add to playlist" << std::endl;
  std::cout << "3. Add to queue" << std::endl;
  std::cout << "0. back" << std::endl;
  std::cout << std::endl;
  std::cout << ">. next " << std::endl;
  std::cout << ">. prev " << std::endl;
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
                         [&playlistName](const Playlist &pl)
                         { return pl.name == playlistName; });
  if (it != playlists.end())
  {
    std::cout << "\nSongs in playlist '" << playlistName << "':" << std::endl;
    node<Song> *current = it->songs.head();
    node<Song> *start = current;

    while (current)
    {
      std::cout << "- " << current->data.title << " - " << current->data.artist << std::endl;
      current = it->songs.next(current);

      // Stop if we've looped back to the start or reached the end
      if (current == start || current == nullptr)
        break;
    }
  }
  else
  {
    throw std::runtime_error("Playlist \"" + playlistName + "\" not found.");
  }
}