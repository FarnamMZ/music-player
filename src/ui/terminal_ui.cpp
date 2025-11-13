#include "ui/terminal_ui.hpp"
#include "utils/logger.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

TerminalUI::TerminalUI(AudioPlayer *player)
    : player_(player), running_(false)
{
}

TerminalUI::~TerminalUI()
{
    cleanup();
}

bool TerminalUI::initialize()
{
    // TODO: Initialize ncurses or other terminal UI library
    Logger::getInstance().log(LogLevel::INFO, "Terminal UI initialized");
    return true;
}

void TerminalUI::run()
{
    running_ = true;

    std::cout << "=== Terminal Music Player ===" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;

    while (running_)
    {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty())
        {
            processCommand(input);
        }
    }
}

void TerminalUI::cleanup()
{
    // TODO: Cleanup ncurses or terminal UI
    Logger::getInstance().log(LogLevel::INFO, "Terminal UI cleaned up");
}

void TerminalUI::drawHeader()
{
    // TODO: Implement header drawing
}

void TerminalUI::drawPlaylist()
{
    // TODO: Implement playlist display
}

void TerminalUI::drawControls()
{
    // TODO: Implement controls display
}

void TerminalUI::drawProgressBar()
{
    // TODO: Implement progress bar
}

void TerminalUI::drawFooter()
{
    // TODO: Implement footer
}

void TerminalUI::handleInput(int /* key */)
{
    // TODO: Handle keyboard input
}

void TerminalUI::processCommand(const std::string &command)
{
    if (command == "help")
    {
        showHelp();
    }
    else if (command == "play")
    {
        player_->play();
        std::cout << "Playing..." << std::endl;
    }
    else if (command == "pause")
    {
        player_->pause();
        std::cout << "Paused." << std::endl;
    }
    else if (command == "stop")
    {
        player_->stop();
        std::cout << "Stopped." << std::endl;
    }
    else if (command == "next")
    {
        player_->next();
        std::cout << "Next track." << std::endl;
    }
    else if (command == "prev" || command == "previous")
    {
        player_->previous();
        std::cout << "Previous track." << std::endl;
    }
    else if (command == "quit" || command == "exit")
    {
        running_ = false;
        std::cout << "Goodbye!" << std::endl;
    }
    else if (command.rfind("add ", 0) == 0)
    {
        std::string filepath = command.substr(4);
        if (player_->addToPlaylist(filepath))
        {
            std::cout << "Added to playlist: " << filepath << std::endl;
        }
        else
        {
            std::cout << "Failed to add file." << std::endl;
        }
    }
    else if (command == "list")
    {
        const auto &playlist = player_->getPlaylist();
        for (size_t i = 0; i < playlist.getSize(); ++i)
        {
            const auto &song = playlist.getSong(i);
            std::cout << i + 1 << ". " << song.title << " - " << song.artist << std::endl;
        }
    }
    else
    {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

void TerminalUI::refreshScreen()
{
    // TODO: Refresh the screen
}

std::string TerminalUI::formatTime(std::chrono::seconds time) const
{
    int minutes = time.count() / 60;
    int seconds = time.count() % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

void TerminalUI::showHelp()
{
    std::cout << "\nAvailable Commands:\n";
    std::cout << "  play           - Start/resume playback\n";
    std::cout << "  pause          - Pause playback\n";
    std::cout << "  stop           - Stop playback\n";
    std::cout << "  next           - Play next track\n";
    std::cout << "  prev/previous  - Play previous track\n";
    std::cout << "  add <file>     - Add file to playlist\n";
    std::cout << "  list           - Show playlist\n";
    std::cout << "  help           - Show this help\n";
    std::cout << "  quit/exit      - Exit the player\n";
}
