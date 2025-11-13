#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <vector>
#include <string>
#include "types.hpp"

class Playlist
{
public:
    Playlist();
    ~Playlist();

    // Add/Remove songs
    bool addSong(const std::string &filepath);
    bool removeSong(size_t index);
    void clear();

    // Access songs
    const Song &getSong(size_t index) const;
    size_t getSize() const;
    bool isEmpty() const;

    // Playlist operations
    void shuffle();
    void sort(bool byArtist = false);

    // Search
    std::vector<size_t> search(const std::string &query) const;

    // File operations
    bool loadFromFile(const std::string &filepath);
    bool saveToFile(const std::string &filepath) const;

private:
    std::vector<Song> songs_;

    bool isAudioFile(const std::string &filepath) const;
    Song loadMetadata(const std::string &filepath);
};

#endif // PLAYLIST_HPP
