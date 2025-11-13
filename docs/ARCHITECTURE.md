# Architecture

## Overview

The Terminal Music Player is structured in a modular architecture with clear separation of concerns:

```
┌─────────────────┐
│   Terminal UI   │  ← User Interface Layer
└────────┬────────┘
         │
┌────────▼────────┐
│  Audio Player   │  ← Application Logic Layer
└────────┬────────┘
         │
    ┌────┴────┐
    │         │
┌───▼──┐  ┌──▼────────┐
│Playlist│ │Audio Engine│  ← Audio Processing Layer
└───┬──┘  └──┬────────┘
    │        │
    │    ┌───▼─────────┐
    │    │Audio Decoder│
    │    └─────────────┘
    │
┌───▼─────────┐
│File Manager │  ← Utilities Layer
└─────────────┘
```

## Components

### 1. Terminal UI (`ui/terminal_ui.hpp`)
- Handles user input and display
- Uses ncurses for terminal manipulation
- Displays playlist, controls, and playback status

### 2. Audio Player (`audio_player.hpp`)
- Main application controller
- Manages playback state
- Coordinates between playlist and audio engine

### 3. Playlist (`playlist.hpp`)
- Manages collection of songs
- Provides search and sort functionality
- Handles playlist file I/O

### 4. Audio Engine (`audio/audio_engine.hpp`)
- Low-level audio playback
- Uses SDL2 or PortAudio
- Manages audio device and stream

### 5. Audio Decoder (`audio/audio_decoder.hpp`)
- Decodes various audio formats
- Factory pattern for format-specific decoders
- Provides PCM audio data to engine

### 6. File Manager (`utils/file_manager.hpp`)
- File system operations
- Audio file detection
- Path manipulation

### 7. Logger (`utils/logger.hpp`)
- Centralized logging
- Thread-safe logging
- File and console output

## Design Patterns

- **Singleton**: Logger
- **Factory**: AudioDecoder creation
- **Observer**: (To be implemented for playback events)

## Threading Model

- Main thread: UI and user input
- Audio thread: Audio playback callback
- (Future) Background thread: Metadata loading

## Dependencies

- **SDL2** or **PortAudio**: Audio I/O
- **libmpg123**: MP3 decoding
- **libsndfile**: WAV/FLAC/OGG decoding
- **TagLib**: Metadata reading
- **ncurses**: Terminal UI

## Future Enhancements

1. Visualizer using FFT
2. Equalizer
3. Network streaming support
4. Playlist collaboration
5. Plugin system for decoders
