#ifndef TERMINAL_UI_HPP
#define TERMINAL_UI_HPP

#include <string>
#include <memory>
#include "audio_player.hpp"

class TerminalUI
{
public:
    explicit TerminalUI(AudioPlayer *player);
    ~TerminalUI();

    bool initialize();
    void run();
    void cleanup();

private:
    AudioPlayer *player_;
    bool running_;

    // UI Components
    void drawHeader();
    void drawPlaylist();
    void drawControls();
    void drawProgressBar();
    void drawFooter();

    // Input handling
    void handleInput(int key);
    void processCommand(const std::string &command);

    // Helper functions
    void refreshScreen();
    std::string formatTime(std::chrono::seconds time) const;
    void showHelp();
};

#endif // TERMINAL_UI_HPP
