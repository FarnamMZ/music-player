#include "audio_player.hpp"
#include "utils/logger.hpp"

AudioPlayer::AudioPlayer()
    : audioEngine_(std::make_unique<AudioEngine>()),
      state_(PlaybackState::STOPPED),
      volume_(1.0f),
      currentTrackIndex_(-1)
{
}

AudioPlayer::~AudioPlayer()
{
    stop();
}

bool AudioPlayer::play()
{
    if (playlist_.isEmpty())
    {
        Logger::getInstance().log(LogLevel::WARNING, "Cannot play: playlist is empty");
        return false;
    }

    if (state_ == PlaybackState::PAUSED)
    {
        state_ = PlaybackState::PLAYING;
        return audioEngine_->play();
    }

    if (currentTrackIndex_ < 0)
    {
        currentTrackIndex_ = 0;
    }

    loadTrack(currentTrackIndex_);
    state_ = PlaybackState::PLAYING;
    return audioEngine_->play();
}

bool AudioPlayer::pause()
{
    if (state_ == PlaybackState::PLAYING)
    {
        state_ = PlaybackState::PAUSED;
        return audioEngine_->pause();
    }
    return false;
}

bool AudioPlayer::stop()
{
    state_ = PlaybackState::STOPPED;
    return audioEngine_->stop();
}

bool AudioPlayer::next()
{
    if (playlist_.isEmpty())
    {
        return false;
    }

    currentTrackIndex_ = (currentTrackIndex_ + 1) % playlist_.getSize();
    return play();
}

bool AudioPlayer::previous()
{
    if (playlist_.isEmpty())
    {
        return false;
    }

    currentTrackIndex_ = (currentTrackIndex_ - 1 + playlist_.getSize()) % playlist_.getSize();
    return play();
}

bool AudioPlayer::loadPlaylist(const std::string &path)
{
    return playlist_.loadFromFile(path);
}

bool AudioPlayer::addToPlaylist(const std::string &filepath)
{
    return playlist_.addSong(filepath);
}

void AudioPlayer::clearPlaylist()
{
    stop();
    playlist_.clear();
    currentTrackIndex_ = -1;
}

Playlist &AudioPlayer::getPlaylist()
{
    return playlist_;
}

const Playlist &AudioPlayer::getPlaylist() const
{
    return playlist_;
}

PlaybackInfo AudioPlayer::getPlaybackInfo() const
{
    PlaybackInfo info;
    info.state = state_;
    info.currentTime = audioEngine_->getCurrentPosition();
    info.totalTime = audioEngine_->getDuration();
    info.volume = volume_;
    info.currentTrackIndex = currentTrackIndex_;
    return info;
}

bool AudioPlayer::isPlaying() const
{
    return state_ == PlaybackState::PLAYING;
}

void AudioPlayer::loadTrack(int index)
{
    if (index >= 0 && index < static_cast<int>(playlist_.getSize()))
    {
        const auto &song = playlist_.getSong(index);
        audioEngine_->load(song.filepath);
        Logger::getInstance().log(LogLevel::INFO, "Loaded: " + song.title);
    }
}
