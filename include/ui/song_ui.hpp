#pragma once
#include "types.hpp"

class SongUI
{
private:
    Song currentSong_;

    // UI Components
    void drawSongPage();
    void drawPlaylistsContainingSong();
    void drawExistedPlaylists();
    void drawSongsInPlaylist(const std::string &playlistName);

    // Input handling
    void processCommand(const std::string &command, bool &running);

public:
    SongUI(Song song) : currentSong_(song) {};
    void run();
};
