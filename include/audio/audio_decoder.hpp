#ifndef AUDIO_DECODER_HPP
#define AUDIO_DECODER_HPP

#include <string>
#include <vector>
#include <chrono>

class AudioDecoder
{
public:
    AudioDecoder();
    virtual ~AudioDecoder();

    // File operations
    virtual bool open(const std::string &filepath) = 0;
    virtual void close() = 0;

    // Decoding
    virtual size_t read(float *buffer, size_t frames) = 0;
    virtual void seek(std::chrono::seconds position) = 0;

    // Info
    virtual std::chrono::seconds getDuration() const = 0;
    virtual int getSampleRate() const = 0;
    virtual int getChannels() const = 0;

    // Factory method
    static std::unique_ptr<AudioDecoder> createForFile(const std::string &filepath);

protected:
    std::string filepath_;
    int sampleRate_;
    int channels_;
    std::chrono::seconds duration_;
};

#endif // AUDIO_DECODER_HPP
