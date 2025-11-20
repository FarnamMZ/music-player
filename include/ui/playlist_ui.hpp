#pragma once
#include <iostream>
#include "types.hpp"
#include "cdll.hpp"

class PlaylistUI
{
public:
    void run();
    PlaylistUI(Playlist *playlist) : currentPlaylist_(playlist) {}

private:
    // Pointer to the playlist
    Playlist *currentPlaylist_;

    // UI Components
    void drawPlaylistPage();
    // void drawCurrentSongInCDLL();

    // Input handling
    void processCommand(const std::string &command, bool &running);

    void deleteSong(int index);
};