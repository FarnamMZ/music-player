#pragma once
#include <iostream>
#include "types.hpp"

class SongsUI
{
  public:
    SongsUI();
    void run();
  private:
    // list of songs
    std::vector<Song> songs_;

    // UI Components
    void drawSongs();

    // Input handling
    void processCommand(const std::string &command, bool &running);

    // add a song to the list in alphabetical order
    void addSong(const Song &song);
};
