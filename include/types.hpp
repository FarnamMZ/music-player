#pragma once
#include <string>

// Represents a single audio track
struct Song
{
    std::string title;
    std::string artist;
    std::string album;
    std::string filepath;
    int duration; // Duration in seconds
};

