#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <chrono>

enum class PlaybackState
{
    STOPPED,
    PLAYING,
    PAUSED
};

enum class RepeatMode
{
    NONE,
    ONE,
    ALL
};

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

struct Song
{
    std::string filepath;
    std::string title;
    std::string artist;
    std::string album;
    std::chrono::seconds duration;
    int bitrate;

    Song() : duration(0), bitrate(0) {}
};

struct PlaybackInfo
{
    PlaybackState state;
    std::chrono::seconds currentTime;
    std::chrono::seconds totalTime;
    float volume;
    int currentTrackIndex;

    PlaybackInfo()
        : state(PlaybackState::STOPPED),
          currentTime(0),
          totalTime(0),
          volume(1.0f),
          currentTrackIndex(-1) {}
};

#endif // TYPES_HPP
