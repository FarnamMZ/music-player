#include <iostream>
#include <memory>
#include "audio_player.hpp"
#include "ui/terminal_ui.hpp"
#include "utils/logger.hpp"

int main(int argc, char *argv[])
{
    try
    {
        // Initialize logger
        Logger::getInstance().log(LogLevel::INFO, "Starting Music Player...");

        // Create audio player instance
        auto player = std::make_unique<AudioPlayer>();

        // Create terminal UI
        auto ui = std::make_unique<TerminalUI>(player.get());

        // Initialize UI
        if (!ui->initialize())
        {
            Logger::getInstance().log(LogLevel::ERROR, "Failed to initialize UI");
            return 1;
        }

        // Run the application
        ui->run();

        // Cleanup
        ui->cleanup();

        Logger::getInstance().log(LogLevel::INFO, "Music Player stopped.");
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
