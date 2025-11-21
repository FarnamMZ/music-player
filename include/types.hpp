#pragma once
#include <string>
#include <vector>
#include "cdll.hpp"

// Represents a single audio track
struct Song
{
    std::string title;
    std::string artist;
    std::string filepath;
    int duration; // Duration in seconds

    // Equality operator for std::find and comparisons
    bool operator==(const Song &other) const
    {
        return title == other.title && artist == other.artist;
    }
};

// Represents a playlist of songs
struct Playlist
{
    std::string name;
    cdll<Song> songs;
};

enum class PlayerSource
{
    NONE,
    PLAYLIST,
    QUEUE
};

// sample songs
static std::vector<Song> sampleSongs = {
    {"Song A", "Artist 1", "/path/to/songA.mp3", 210},
    {"Song B", "Artist 2", "/path/to/songB.mp3", 180},
    {"Song C", "Artist 3", "/path/to/songC.mp3", 240},
    {"Song D", "Artist 4", "/path/to/songD.mp3", 200}};