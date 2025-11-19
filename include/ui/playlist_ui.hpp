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

    // songs cdll
    cdll<Song> songs_;
    node<Song> *lastSong_ = nullptr;
    void loadSongsIntoCDLL(int startIndex);

    // current song node pointer
    node<Song> *currentSong_ = nullptr;

    // UI Components
    void drawPlaylistPage();
    void drawCurrentSongInCDLL();

    // Input handling
    void processCommand(const std::string &command, bool &running);

    void deleteSong(int index);
};