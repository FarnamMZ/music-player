#include "ui/Main.hpp"
#include "ui/queue_ui.hpp"
#include "ui/playlists_ui.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

// Define the static member variables
std::vector<Playlist> Main::playlists_;
std::queue<Song> Main::songQueue_;
Player *Main::player_;
std::stack<Player *> Main::playersStack_;

Main::Main()
{
  // Initialize player
  player_ = new Player();
  playersStack_ = std::stack<Player *>();
}

Main::~Main()
{
  // Clean up players
  if (player_)
  {
    delete player_;
    player_ = nullptr;
  }

  // Clean up players in stack
  while (!playersStack_.empty())
  {
    Player *p = playersStack_.top();
    playersStack_.pop();
    delete p;
  }
}

// Player management functions
void Main::pushPlayer(Player *player)
{
  playersStack_.push(player);
  player_ = playersStack_.top();
}

void Main::popPlayer()
{
  if (!playersStack_.empty())
  {
    Player *oldPlayer = playersStack_.top();
    playersStack_.pop();
    delete oldPlayer;

    // Restore previous player or default
    if (!playersStack_.empty())
    {
      player_ = playersStack_.top();
    }
    else
    {
      player_ = new Player(); // Default player
    }
  }
}

void Main::checkAndPopFinishedPlayer()
{
  if (player_ && player_->isFinished())
  {
    popPlayer();
  }
}

bool Main::isPlaylistCurrentlyPlaying(Playlist *playlist)
{
  // Check if the current player is playing this playlist
  if (player_ && player_->getPlaylist() == playlist)
  {
    return true;
  }
  return false;
}

void Main::run()
{
  bool running = true;

  clearScreen();
  drawMainPage();

  while (running)
  {
    // Check if current player is finished
    checkAndPopFinishedPlayer();

    std::cout << "\n> ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty())
    {
      processCommand(input, running);
      if (running)
      {
        clearScreen();
        drawMainPage();
      }
    }
  }
}

void Main::processCommand(const std::string &command, bool &running)
{
  if (command == "next")
  {
    Main::player_->next();
    Main::checkAndPopFinishedPlayer(); // Check if finished after next
  }
  else if (command == "prev")
  {
    Main::player_->prev();
    Main::checkAndPopFinishedPlayer(); // Check if finished after prev
  }
  else if (command == "1")
  {
    SongsUI songsUI;
    songsUI.run();
  }
  else if (command == "2")
  {
    PlaylistsUI playlistsUI;
    playlistsUI.run();
  }
  else if (command == "3")
  {
    QueueUI queueUI;
    queueUI.run();
  }
  else if (command == "0")
  {
    running = false;
  }
  else
  {
    std::cout << "unknown command\n"
              << std::endl;
  }
}

// UI Components
void Main::drawMainPage()
{
  Main::player_->drawPlayerHeader();
  std::cout << std::endl;
  std::cout << "=== Terminal Music Player ===" << std::endl;
  std::cout << "main page" << std::endl;
  std::cout << "1. songs" << std::endl;
  std::cout << "2. playlists" << std::endl;
  std::cout << "3. song queue" << std::endl;
  std::cout << "0. exit" << std::endl;
  std::cout << std::endl;
  std::cout << ">. next " << std::endl;
  std::cout << ">. prev " << std::endl;
}

void Main::clearScreen()
{
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

// Playlist management functions
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

// Queue management functions
void Main::addToQueue(const Song &song)
{
  songQueue_.push(song);
  std::cout << "Added \"" << song.title << "\" to queue." << std::endl;
}

void Main::displayQueue()
{
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
