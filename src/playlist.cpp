#include "playlist.hpp"
#include "utils/file_manager.hpp"
#include "utils/logger.hpp"
#include <algorithm>
#include <fstream>
#include <random>

Playlist::Playlist()
{
}

Playlist::~Playlist()
{
}

bool Playlist::addSong(const std::string &filepath)
{
    if (!FileManager::fileExists(filepath))
    {
        Logger::getInstance().log(LogLevel::ERROR, "File not found: " + filepath);
        return false;
    }

    if (!isAudioFile(filepath))
    {
        Logger::getInstance().log(LogLevel::WARNING, "Not an audio file: " + filepath);
        return false;
    }

    Song song = loadMetadata(filepath);
    songs_.push_back(song);

    Logger::getInstance().log(LogLevel::INFO, "Added to playlist: " + song.title);
    return true;
}

bool Playlist::removeSong(size_t index)
{
    if (index >= songs_.size())
    {
        return false;
    }

    songs_.erase(songs_.begin() + index);
    return true;
}

void Playlist::clear()
{
    songs_.clear();
}

const Song &Playlist::getSong(size_t index) const
{
    return songs_.at(index);
}

size_t Playlist::getSize() const
{
    return songs_.size();
}

bool Playlist::isEmpty() const
{
    return songs_.empty();
}

void Playlist::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(songs_.begin(), songs_.end(), g);
}

void Playlist::sort(bool byArtist)
{
    if (byArtist)
    {
        std::sort(songs_.begin(), songs_.end(),
                  [](const Song &a, const Song &b)
                  { return a.artist < b.artist; });
    }
    else
    {
        std::sort(songs_.begin(), songs_.end(),
                  [](const Song &a, const Song &b)
                  { return a.title < b.title; });
    }
}

std::vector<size_t> Playlist::search(const std::string &query) const
{
    std::vector<size_t> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (size_t i = 0; i < songs_.size(); ++i)
    {
        std::string title = songs_[i].title;
        std::string artist = songs_[i].artist;
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(artist.begin(), artist.end(), artist.begin(), ::tolower);

        if (title.find(lowerQuery) != std::string::npos ||
            artist.find(lowerQuery) != std::string::npos)
        {
            results.push_back(i);
        }
    }

    return results;
}

bool Playlist::loadFromFile(const std::string & /* filepath */)
{
    // TODO: Implement playlist file loading (M3U, PLS format)
    return false;
}

bool Playlist::saveToFile(const std::string & /* filepath */) const
{
    // TODO: Implement playlist file saving
    return false;
}

bool Playlist::isAudioFile(const std::string &filepath) const
{
    return FileManager::isAudioFile(filepath);
}

Song Playlist::loadMetadata(const std::string &filepath)
{
    Song song;
    song.filepath = filepath;
    song.title = FileManager::getFilename(filepath);
    song.artist = "Unknown Artist";
    song.album = "Unknown Album";

    // TODO: Load actual metadata using a library like TagLib

    return song;
}
