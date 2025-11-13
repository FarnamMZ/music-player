cmake_minimum_required(VERSION 3.15)
project(MusicPlayer VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find required packages
find_package(Threads REQUIRED)

# Uncomment when you add the libraries
# find_package(SDL2 REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(MPG123 REQUIRED libmpg123)

# Source files
set(SOURCES
    src/main.cpp
    src/audio_player.cpp
    src/playlist.cpp
    src/ui/terminal_ui.cpp
    src/audio/audio_engine.cpp
    src/audio/audio_decoder.cpp
    src/utils/file_manager.cpp
    src/utils/logger.cpp
)

# Header files
set(HEADERS
    include/audio_player.hpp
    include/playlist.hpp
    include/ui/terminal_ui.hpp
    include/audio/audio_engine.hpp
    include/audio/audio_decoder.hpp
    include/utils/file_manager.hpp
    include/utils/logger.hpp
    include/types.hpp
)

# Create executable
add_executable(music-player ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(music-player 
    PRIVATE 
    Threads::Threads
    # ${SDL2_LIBRARIES}
    # ${MPG123_LIBRARIES}
    # ncurses
)

# Installation
install(TARGETS music-player DESTINATION bin)

# Enable testing
enable_testing()
add_subdirectory(tests)
