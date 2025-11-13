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

    while (running_)
    {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty())
        {
          if (input == "0") running_ = false;
          processCommand(input);
        }
    }
}

void TerminalUI::cleanup()
{
    // TODO: Cleanup ncurses or terminal UI
    Logger::getInstance().log(LogLevel::INFO, "Terminal UI cleaned up");
}

void Terminal::drawMainPage()
{
  std::cout << "main player" << std::endl;
  std::cout << "1. songs" << std::endl;
  std::cout << "2. playlists" << std::endl;
  std::cout << "3. song queue" << std::endl;
  std::cout << "0. exit" << std::endl;
}

void TerminalUI::processCommand(const std::string &command)
{
  if (command == "1") {
    songsUI::run()
  }
  else if (command == "2") {
   // TODO 
  }
  else if (command == "3") {
   // TODO 
  }
  else {
    std::cout << "unkown command" << std::endl;
  }
  return false;
}

void TerminalUI::refreshScreen()
{
    // TODO: Refresh the screen
}

