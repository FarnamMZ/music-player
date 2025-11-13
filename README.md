# Terminal Music Player

A command-line music player built with C++.

## Features

- Play audio files (MP3, WAV, FLAC, etc.)
- Playlist management
- Playback controls (play, pause, stop, next, previous)
- Volume control
- Audio visualization in terminal
- Search and filter songs

## Project Structure

```
music-player/
├── src/              # Source files
├── include/          # Header files
├── lib/              # External libraries
├── assets/           # Sample audio files and resources
├── tests/            # Unit tests
├── build/            # Build output
└── docs/             # Documentation
```

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Running

```bash
./build/music-player
```

## Dependencies

- SDL2 or PortAudio (for audio playback)
- libmpg123 or libsndfile (for audio decoding)
- ncurses (for terminal UI)

## License

MIT License
