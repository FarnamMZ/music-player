#pragma once
#include <iostream>
#include "types.hpp"

class PlaylistsUI
{
public:
    void run();
private:
    // UI Components
    void drawPlaylistsPage();

    // Input handling
    void processCommand(const std::string &command, bool &running);

    void addNewPlaylist();
    bool playlistExists(const std::string &playlistName);
};