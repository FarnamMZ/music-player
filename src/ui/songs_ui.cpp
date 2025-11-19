#include "ui/songs_ui.hpp"
#include "ui/song_ui.hpp"
#include "ui/Main.hpp"
#include <iostream>

SongsUI::SongsUI()
{
  // Example songs added for demonstration
  addSong(sampleSongs[0]);
  addSong(sampleSongs[1]);
  addSong(sampleSongs[2]);
  addSong(sampleSongs[3]);
}

void SongsUI::run()
{
  bool running = true;

  Main::clearScreen();
  std::cout << "=== List of songs ===" << std::endl;
  drawSongs();

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
        std::cout << "=== List of songs ===" << std::endl;
        drawSongs();
      }
    }
  }
}

void SongsUI::processCommand(const std::string &command, bool &running)
{
  // check if i is a number
  if (std::isdigit(command[0]))
  {
    int songIndex = std::stoi(command);
    if (songIndex > 0 && songIndex <= static_cast<int>(songs_.size()))
    {
      SongUI songUI(songs_[songIndex - 1]);
      songUI.run();
    }
    else if (songIndex == 0)
    {
      running = false;
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

void SongsUI::drawSongs()
{
  std::cout << "Songs List:" << std::endl;
  int index = 1;
  for (const auto &song : songs_)
  {
    std::cout << index++ << ". " << song.title << ", " << song.artist << std::endl;
  }
  std::cout << "0. back" << std::endl;
}

void SongsUI::addSong(const Song &song)
{
  auto it = std::lower_bound(songs_.begin(), songs_.end(), song,
                             [](const Song &a, const Song &b)
                             { return a.title < b.title; });
  songs_.insert(it, song);
}