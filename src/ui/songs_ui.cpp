#include "ui/songs_ui.hpp"

void SongsUI::run()
{
  running_ = true;

  std::cout << "=== List of songs ===" << std::endl;

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
