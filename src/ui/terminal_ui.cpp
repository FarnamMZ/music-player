#include "ui/terminal_ui.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

TerminalUI::~TerminalUI()
{
    cleanup();
}

bool TerminalUI::initialize()
{
    // TODO: Initialize ncurses or other terminal UI library
    return true;
}

void TerminalUI::run()
{
    bool running = true;

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
          drawMainPage();
        }
    }
}

void TerminalUI::cleanup()
{
    // TODO: Cleanup ncurses or terminal UI
}

void TerminalUI::drawMainPage()
{
  std::cout << "main page" << std::endl;
  std::cout << "1. songs" << std::endl;
  std::cout << "2. playlists" << std::endl;
  std::cout << "3. song queue" << std::endl;
  std::cout << "0. exit" << std::endl;
}

void TerminalUI::processCommand(const std::string &command, bool &running)
{
  if (command == "1") {
    songsUI.run();
  }
  else if (command == "2") {
   // TODO 
  }
  else if (command == "3") {
   // TODO
  }
    else if (command == "0") {
        running = false;
    }
  else {
    std::cout << "unkown command\n" << std::endl;
  }
}

void TerminalUI::refreshScreen()
{
    // TODO: Refresh the screen
}

