#ifndef TERMINAL_UI_HPP
#define TERMINAL_UI_HPP

#include <string>
#include <memory>
#include "audio_player.hpp"
#include "ui/songs_ui.hpp"

class TerminalUI
{
public:
    explicit TerminalUI(AudioPlayer *player);
    ~TerminalUI();

    bool initialize();
    void run();
    void cleanup();

private:
    SongsUI songsUI;
    AudioPlayer *player_;
    bool running_;

    // UI Components
    void drawMainPage();

    // Input handling
    void processCommand(const std::string &command);

    // Helper functions
    void refreshScreen();
};

#endif // TERMINAL_UI_HPP
