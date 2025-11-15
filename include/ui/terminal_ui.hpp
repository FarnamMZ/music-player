#include <string>
#include <memory>
#include "ui/songs_ui.hpp"

class TerminalUI
{
public:
    ~TerminalUI();

    bool initialize();
    void run();
    void cleanup();

private:
    SongsUI songsUI;

    // UI Components
    void drawMainPage();

    // Input handling
    void processCommand(const std::string &command, bool &running);

    // Helper functions
    void refreshScreen();
};
