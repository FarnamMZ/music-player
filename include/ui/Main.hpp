#pragma once
#include <string>
#include <memory>
#include <queue>
#include "ui/songs_ui.hpp"
#include "types.hpp"

class Main
{
public:
    // List of playlists
    static std::vector<Playlist> playlists_;
    
    // Song queue
    static std::queue<Song> songQueue_;

    void run();

    static void clearScreen();

    // Playlist management
    static std::vector<Playlist> getPlaylists(Song &song);
    static void addSongToPlaylist(Song &song, const std::string &playlistName, int position);
    static bool songExistsInPlaylist(const Song &song, const std::string &playlistName);

    // Queue management
    static void addToQueue(const Song &song);
    static void displayQueue();
    static Song getNextFromQueue();
    static bool isQueueEmpty();
private:
    // UI Components
    void drawMainPage();

    // Input handling
    void processCommand(const std::string &command, bool &running);
};
