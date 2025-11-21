#include "ui/songs_ui.hpp"
#include "ui/song_ui.hpp"
#include "ui/Main.hpp"
#include <iostream>

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
  // check if i is a number
  else if (std::isdigit(command[0]))
  {
    int songIndex = std::stoi(command);
    if (songIndex > 0 && songIndex <= static_cast<int>(Main::songs_.size()))
    {
      SongUI songUI(&Main::songs_[songIndex - 1]);
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
  Main::player_->drawPlayerHeader();
  std::cout << std::endl;
  std::cout << "Songs List:" << std::endl;
  int index = 1;
  for (const auto &song : Main::songs_)
  {
    std::cout << index++ << ". " << song.title << ", " << song.artist << std::endl;
  }
  std::cout << "0. back" << std::endl;
  std::cout << std::endl;
  std::cout << ">. next " << std::endl;
  std::cout << ">. prev " << std::endl;
}

void SongsUI::addSong(const Song &song)
{
  auto it = std::lower_bound(Main::songs_.begin(), Main::songs_.end(), song,
                             [](const Song &a, const Song &b)
                             { return a.title < b.title; });
  Main::songs_.insert(it, song);
}