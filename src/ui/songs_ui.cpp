#include "ui/songs_ui.hpp"
#include "ui/song_ui.hpp"
#include <iostream>

SongsUI::SongsUI()
{
    // Example songs added for demonstration
    addSong({"Song A", "Artist A", "Album A", "/path/to/songA.mp3", 210});
    addSong({"Song C", "Artist C", "Album C", "/path/to/songC.mp3", 200});
    addSong({"Song B", "Artist B", "Album B", "/path/to/songB.mp3", 180});
}

void SongsUI::run()
{
  bool running = true;

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
      drawSongs();
    }
  }
}

void SongsUI::processCommand(const std::string &command, bool &running)
{
  // check if i is a number
  if (std::isdigit(command[0])) {
    int songIndex = std::stoi(command);
    if (songIndex > 0 && songIndex <= songs_.size()) {
      SongUI songUI(songs_[songIndex - 1]);
      songUI.run();
    }
    else if (songIndex == 0) {
      running = false;
    }
    else {
      std::cout << "Invalid song number" << std::endl;
    }
  }
  else {
    std::cout << "unknown command" << std::endl;
  }
}

void SongsUI::drawSongs()
{
  std::cout << "Songs List:" << std::endl;
  int index = 1;
  for (const auto &song : songs_) {
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