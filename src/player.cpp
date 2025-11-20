#include "player.hpp"
#include <iostream>

PlaylistPlayer::PlaylistPlayer(Playlist *playlist, int startIndex)
{
    currentPlaylist_ = playlist;
    source_ = PlayerSource::PLAYLIST; // Set the source

    // clear existing songs in the cdll
    songs_.clearAll();

    // Load songs from the current playlist into the circular doubly linked list
    for (int i = startIndex; i < static_cast<int>(currentPlaylist_->songs.size()); i++)
    {
        songs_.insert(currentPlaylist_->songs[i]);
    }
    for (int i = 0; i < startIndex; i++)
    {
        songs_.insert(currentPlaylist_->songs[i]);
    }

    currentSong_ = songs_.tail();
    lastSong_ = songs_.tail();
}

void PlaylistPlayer::next()
{
    if (currentSong_)
    {
        currentSong_ = songs_.prev(currentSong_);
        if (currentSong_ == lastSong_)
            currentSong_ = nullptr;
    }
}

void PlaylistPlayer::prev()
{
    if (currentSong_)
    {
        currentSong_ = songs_.next(currentSong_);
        if (currentSong_ == lastSong_)
            currentSong_ = nullptr;
    }
}

void PlaylistPlayer::drawPlayerHeader()
{
    std::cout << "song playing: " << (currentSong_ ? currentSong_->data.title : "None") << std::endl;
    std::cout << "source: " << currentPlaylist_->name << std::endl;
}

bool PlaylistPlayer::isFinished() const
{
    return currentSong_ == nullptr;
}

Playlist *PlaylistPlayer::getPlaylist() const
{
    return currentPlaylist_;
}