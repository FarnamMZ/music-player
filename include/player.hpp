#pragma once
#include "types.hpp"
#include "cdll.hpp"
#include <queue>
#include <iostream>

// Base Player class with default "do nothing" implementations
class Player
{
public:
    Player() = default;
    virtual ~Player() = default;

    // Virtual functions with default implementations (do nothing)
    virtual void next()
    {
        // Default: do nothing
    }

    virtual void prev()
    {
        // Default: do nothing
    }

    virtual void drawPlayerHeader()
    {
        // Default: show no song playing
        std::cout << "No song playing" << std::endl;
        std::cout << "Source: None" << std::endl;
    }

    // Check if player has finished playing
    virtual bool isFinished() const
    {
        return false; // Default player never finishes
    }

    // Get the current playlist (if any)
    virtual Playlist *getPlaylist() const
    {
        return nullptr; // Default player has no playlist
    }

    PlayerSource getSource() const { return source_; }

protected:
    PlayerSource source_ = PlayerSource::NONE;
};

// PlaylistPlayer implementation
class PlaylistPlayer : public Player
{
private:
    Playlist *currentPlaylist_;
    node<Song> *currentSong_;
    node<Song> *lastSong_;

public:
    PlaylistPlayer(Playlist *playlist, int startIndex);
    ~PlaylistPlayer() override = default;

    // Override virtual functions from Player interface
    void next() override;
    void prev() override;
    void drawPlayerHeader() override;
    bool isFinished() const override;
    Playlist *getPlaylist() const override;

    // Move currentSong_ to next if it matches the node being deleted
    void moveCurrentSongIfMatches(node<Song> *nodeToDelete);
};

class QueuePlayer : public Player
{
private:
    Song *currentSong_;

public:
    QueuePlayer();
    ~QueuePlayer() override = default;

    void next() override;
    void drawPlayerHeader() override;
    bool isFinished() const override;
};
