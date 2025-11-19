#include "ui/queue_ui.hpp"
#include "ui/song_ui.hpp"
#include "ui/Main.hpp"

void QueueUI::run()
{
    bool running = true;

    Main::clearScreen();
    drawQueuePage();

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
                Main::clearScreen();
                drawQueuePage();
            }
        }
    }
}

void QueueUI::drawQueuePage()
{
    std::cout << "=== Song Queue ===" << std::endl;
    Main::displayQueue();
    std::cout << "\n-1. play" << std::endl;
    std::cout << "\n0. back" << std::endl;
}

void QueueUI::processCommand(const std::string &command, bool &running)
{
    // check if command is a number
    if (std::isdigit(command[0]) || (command[0] == '-' && command.size() > 1 && std::isdigit(command[1])))
    {
        int cmdNum = std::stoi(command);
        if (cmdNum == -1)
        {
            // TODO
        }
        else if (cmdNum == 0)
        {
            running = false;
        }
        // check if cmdNum is in range of queue numbers starting from 1
        else if (cmdNum > 0 && cmdNum <= static_cast<int>(Main::songQueue_.size()))
        {
            // get the song at position cmdNum in the queue
            std::queue<Song> tempQueue = Main::songQueue_;
            Song selectedSong;
            for (int i = 1; i <= cmdNum; ++i)
            {
                selectedSong = tempQueue.front();
                tempQueue.pop();
            }
            SongUI songUI(selectedSong);
            songUI.run();
        }
        else
        {
            std::cout << "invalid song number" << std::endl;
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
    else
    {
        std::cout << "unknown command" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
}