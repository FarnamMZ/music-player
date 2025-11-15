#include "ui/song_ui.hpp"
#include <iostream>

void SongUI::run()
{
  bool running = true;

  std::cout << currentSong_.title << " - " << currentSong_.artist << std::endl;
  drawSongPage();

  while (running)
  {
    std::cout << "\n> ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty())
    {
      // processCommand(input, running);
      drawSongPage();
    }
  }
}

void SongUI::drawSongPage()
{
  std::cout << "1. List of playlists" << std::endl;
  std::cout << "2. Add to playlist" << std::endl;
  std::cout << "3. Add to queue" << std::endl;
  std::cout << "0. back" << std::endl;
}