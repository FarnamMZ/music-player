#include "ui/Main.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

// Define the static member variable
std::vector<Playlist> Main::playlists_;
std::queue<Song> Main::songQueue_;

Main::Main()
{
  // Initialize playlists from sample songs
  playlists_ = {
      {"My Favorites", {sampleSongs[0], sampleSongs[1]}},
      {"Chill Vibes", {sampleSongs[2], sampleSongs[3]}}};
}

Main::~Main()
{
  cleanup();
}

bool Main::initialize()
{
  // TODO: Initialize ncurses or other terminal UI library
  return true;
}

void Main::run()
{
  bool running = true;

  clearScreen();
  std::cout << "=== Terminal Music Player ===" << std::endl;
  drawMainPage();

  while (running)
  {
    std::cout << "\n> ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty())
    {
      processCommand(input, running);
      if (running)
      {
        clearScreen();
        std::cout << "=== Terminal Music Player ===" << std::endl;
        drawMainPage();
      }
    }
  }
}

void Main::cleanup()
{
  // TODO: Cleanup ncurses or terminal UI
}

void Main::drawMainPage()
{
  std::cout << "main page" << std::endl;
  std::cout << "1. songs" << std::endl;
  std::cout << "2. playlists" << std::endl;
  std::cout << "3. song queue" << std::endl;
  std::cout << "0. exit" << std::endl;
}

void Main::processCommand(const std::string &command, bool &running)
{
  if (command == "1")
  {
    SongsUI songsUI;
    songsUI.run();
  }
  else if (command == "2")
  {
    // TODO
  }
  else if (command == "3")
  {
    // TODO
  }
  else if (command == "0")
  {
    running = false;
  }
  else
  {
    std::cout << "unkown command\n"
              << std::endl;
  }
}

void Main::clearScreen()
{
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

std::vector<Playlist> Main::getPlaylists(Song &song)
{
  std::vector<Playlist> playlists;
  for (const auto &playlist : playlists_)
  {
    if (std::find(playlist.songs.begin(), playlist.songs.end(), song) != playlist.songs.end())
    {
      playlists.push_back(playlist);
    }
  }
  return playlists;
}

void Main::addSongToPlaylist(Song &song, const std::string &playlistName, int position)
{
  auto it = std::find_if(playlists_.begin(), playlists_.end(),
                         [&playlistName](const Playlist &pl)
                         { return pl.name == playlistName; });
  if (it != playlists_.end())
  {    
    if (position < 0)
    {
      // Add at the beginning (before index 0)
      it->songs.insert(it->songs.begin(), song);
      std::cout << "Added \"" << song.title << "\" to playlist \"" << playlistName << "\" at the beginning" << std::endl;
    }
    else if (position >= static_cast<int>(it->songs.size()) - 1)
    {
      // Add at the end (after the last index)
      it->songs.push_back(song);
      std::cout << "Added \"" << song.title << "\" to playlist \"" << playlistName << "\" at the end" << std::endl;
    }
    else
    {
      // Insert after the given index (position + 1)
      it->songs.insert(it->songs.begin() + position + 1, song);
      std::cout << "Added \"" << song.title << "\" to playlist \"" << playlistName << "\" after index " << position << std::endl;
    }
  }
  else
  {
    throw std::runtime_error("Playlist \"" + playlistName + "\" not found.");
  }
}

// Queue management functions
void Main::addToQueue(const Song &song)
{
  songQueue_.push(song);
  std::cout << "Added \"" << song.title << "\" to queue." << std::endl;
}

void Main::displayQueue()
{
  clearScreen();
  std::cout << "=== Song Queue ===" << std::endl;
  
  if (songQueue_.empty())
  {
    std::cout << "Queue is empty." << std::endl;
    return;
  }
  
  // Note: std::queue doesn't support iteration directly
  // We need to copy it to display all items
  std::queue<Song> tempQueue = songQueue_;
  int position = 1;
  
  while (!tempQueue.empty())
  {
    const Song &song = tempQueue.front();
    std::cout << position++ << ". " << song.title << " - " << song.artist << std::endl;
    tempQueue.pop();
  }
  
  std::cout << "\nTotal songs in queue: " << songQueue_.size() << std::endl;
}

Song Main::getNextFromQueue()
{
  if (!songQueue_.empty())
  {
    Song song = songQueue_.front();
    songQueue_.pop();
    return song;
  }
  throw std::runtime_error("Queue is empty!");
}

bool Main::isQueueEmpty()
{
  return songQueue_.empty();
}

bool Main::songExistsInPlaylist(const Song &song, const std::string &playlistName)
{
  auto it = std::find_if(playlists_.begin(), playlists_.end(),
                         [&playlistName](const Playlist &pl)
                         { return pl.name == playlistName; });
  if (it != playlists_.end())
  {
    return std::find(it->songs.begin(), it->songs.end(), song) != it->songs.end();
  }
  throw std::runtime_error("Playlist \"" + playlistName + "\" not found.");
}