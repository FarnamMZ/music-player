#pragma once
#include <iostream>
#include "types.hpp"

class SongsUI
{
public:
  void run();

private:
  // UI Components
  void drawSongs();

  // Input handling
  void processCommand(const std::string &command, bool &running);

  // add a song to the list in alphabetical order
  void addSong(const Song &song);
};
