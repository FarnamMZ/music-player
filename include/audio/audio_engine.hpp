#ifndef AUDIO_ENGINE_HPP
#define AUDIO_ENGINE_HPP

#include <string>
#include <memory>
#include <chrono>
#include "audio_decoder.hpp"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    // Audio control
    bool load(const std::string &filepath);
    bool play();
    bool pause();
    bool stop();

    // Position control
    void seek(std::chrono::seconds position);
    std::chrono::seconds getCurrentPosition() const;
    std::chrono::seconds getDuration() const;

    // Volume control
    void setVolume(float volume);
    float getVolume() const;

    // Status
    bool isPlaying() const;
    bool isLoaded() const;

private:
    std::unique_ptr<AudioDecoder> decoder_;
    bool initialized_;
    bool playing_;
    float volume_;

    // Audio callback (platform-specific)
    void audioCallback(float *buffer, int frames);

    // Platform-specific initialization
    bool initializeAudio();
    void shutdownAudio();
};

#endif // AUDIO_ENGINE_HPP
