#include <iostream>
#include <memory>
#include "ui/Main.hpp"

int main()
{
    try
    {
        // Create main UI
        auto ui = std::make_unique<Main>();

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
