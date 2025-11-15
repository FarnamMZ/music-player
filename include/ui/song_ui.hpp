#include "types.hpp"

class SongUI
{
private:
    Song currentSong_;
    void drawSongPage();
    // void processCommand(const std::string &command, bool &running);
public:
    SongUI(Song song) : currentSong_(song) {};
    void run();
};
