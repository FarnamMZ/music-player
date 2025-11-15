#include <iostream>
#include <memory>
#include "ui/terminal_ui.hpp"

int main(int argc, char *argv[])
{
    try
    {

        // Create terminal UI
        auto ui = std::make_unique<TerminalUI>();

        // Initialize UI
        if (!ui->initialize())
        {
            return 1;
        }

        // Run the application
        ui->run();

        // Cleanup
        ui->cleanup();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
