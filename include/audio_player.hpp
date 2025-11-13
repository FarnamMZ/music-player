#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP

#include <memory>
#include <string>
#include "playlist.hpp"
#include "audio/audio_engine.hpp"
#include "types.hpp"

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    // Playback controls
    bool play();
    bool pause();
    bool stop();
    bool next();
    bool previous();

    // Volume control
    void setVolume(float volume);
    float getVolume() const;

    // Seek functionality
    void seek(std::chrono::seconds position);

    // Playlist management
    bool loadPlaylist(const std::string &path);
    bool addToPlaylist(const std::string &filepath);
    void clearPlaylist();

    Playlist &getPlaylist();
    const Playlist &getPlaylist() const;

    // Status
    PlaybackInfo getPlaybackInfo() const;
    bool isPlaying() const;

private:
    std::unique_ptr<AudioEngine> audioEngine_;
    Playlist playlist_;
    PlaybackState state_;
    float volume_;
    int currentTrackIndex_;

    void loadTrack(int index);
};

#endif // AUDIO_PLAYER_HPP
