#include "player.hpp"
#include "ui/Main.hpp"
#include <iostream>

PlaylistPlayer::PlaylistPlayer(Playlist *playlist, int startIndex)
{
    currentPlaylist_ = playlist;
    source_ = PlayerSource::PLAYLIST; // Set the source

    // Reference the playlist's CDLL directly
    // Find the starting node
    if (currentPlaylist_->songs.isEmpty())
    {
        currentSong_ = nullptr;
        lastSong_ = nullptr;
        return;
    }

    // Navigate to the start index
    node<Song> *temp = currentPlaylist_->songs.head();
    for (int i = 0; i < startIndex && temp; i++)
    {
        temp = currentPlaylist_->songs.next(temp);
    }

    currentSong_ = temp;
    lastSong_ = temp;
}

QueuePlayer::QueuePlayer()
{
    source_ = PlayerSource::QUEUE; // Set the source
    try
    {
        currentSong_ = Main::getNextFromQueue();
    }
    catch (...)
    {
        currentSong_ = nullptr;
    }
}

void PlaylistPlayer::next()
{
    if (currentSong_)
    {
        currentSong_ = currentPlaylist_->songs.next(currentSong_);
        if (currentSong_ == lastSong_)
            currentSong_ = nullptr;
    }
}

void PlaylistPlayer::prev()
{
    if (currentSong_)
    {
        currentSong_ = currentPlaylist_->songs.prev(currentSong_);
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

void PlaylistPlayer::moveCurrentSongIfMatches(node<Song> *nodeToDelete)
{
    if (currentSong_ == nodeToDelete)
    {
        // Move to next song before deletion
        currentSong_ = currentPlaylist_->songs.next(currentSong_);

        // If next points to the node being deleted or head, set to null or head
        if (currentSong_ == nodeToDelete || currentSong_ == lastSong_)
        {
            currentSong_ = nullptr;
        }
    }
}

void QueuePlayer::next()
{
    if (!Main::isQueueEmpty())
    {
        try
        {
            currentSong_ = Main::getNextFromQueue();
        }
        catch (...)
        {
            currentSong_ = nullptr;
        }
    }
    else
    {
        currentSong_ = nullptr;
    }
}

void QueuePlayer::drawPlayerHeader()
{
    std::cout << "song playing: " << (currentSong_ ? currentSong_->title : "None") << std::endl;
    std::cout << "source: Queue" << std::endl;
}

bool QueuePlayer::isFinished() const
{
    return currentSong_ == nullptr && Main::isQueueEmpty();
}
