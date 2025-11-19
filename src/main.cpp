#include <iostream>
#include <memory>
#include "ui/Main.hpp"

int main()
{
    try
    {
        // Create main UI
        auto ui = std::make_unique<Main>();

        // Run the application
        ui->run();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
