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
    Main::player_->drawPlayerHeader();
    std::cout << std::endl;
    std::cout << "=== Song Queue ===" << std::endl;
    Main::displayQueue();
    std::cout << "\n-1. play" << std::endl;
    std::cout << "\n0. back" << std::endl;
    std::cout << std::endl;
    std::cout << ">. next " << std::endl;
    std::cout << ">. prev " << std::endl;
}

void QueueUI::processCommand(const std::string &command, bool &running)
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
    // check if command is a number
    else if (std::isdigit(command[0]) || (command[0] == '-' && command.size() > 1 && std::isdigit(command[1])))
    {
        int cmdNum = std::stoi(command);
        if (cmdNum == -1)
        {
            QueuePlayer *queuePlayer = new QueuePlayer();
            Main::pushPlayer(queuePlayer);
            if (Main::isQueueEmpty())
            {
                std::cout << "Queue is empty. Cannot play." << std::endl;
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }
        }
        else if (cmdNum == 0)
        {
            running = false;
        }
        // check if cmdNum is in range of queue numbers starting from 1
        else if (cmdNum > 0 && cmdNum <= static_cast<int>(Main::songQueue_.size()))
        {
            // get the song at position cmdNum in the queue
            std::queue<Song *> tempQueue = Main::songQueue_;
            Song *selectedSong = nullptr;
            for (int i = 1; i <= cmdNum; ++i)
            {
                selectedSong = tempQueue.front();
                tempQueue.pop();
            }
            if (selectedSong)
            {
                SongUI songUI(selectedSong);
                songUI.run();
            }
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