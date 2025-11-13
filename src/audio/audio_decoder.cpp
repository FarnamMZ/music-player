#include "audio/audio_decoder.hpp"
#include "utils/file_manager.hpp"
#include "utils/logger.hpp"

AudioDecoder::AudioDecoder()
    : sampleRate_(44100), channels_(2), duration_(0)
{
}

AudioDecoder::~AudioDecoder()
{
}

std::unique_ptr<AudioDecoder> AudioDecoder::createForFile(const std::string &filepath)
{
    std::string ext = FileManager::getExtension(filepath);

    // TODO: Create appropriate decoder based on file extension
    // For now, return nullptr as we need to implement specific decoders

    Logger::getInstance().log(LogLevel::WARNING,
                              "No decoder available for file type: " + ext);
    return nullptr;
}

// TODO: Implement specific decoder classes:
// - MP3Decoder (using libmpg123)
// - WAVDecoder (using libsndfile)
// - FLACDecoder (using libsndfile or libFLAC)
