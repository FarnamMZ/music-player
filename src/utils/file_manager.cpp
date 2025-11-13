#include "utils/file_manager.hpp"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

std::vector<std::string> FileManager::listFiles(const std::string &directory)
{
    std::vector<std::string> files;

    try
    {
        for (const auto &entry : fs::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path().string());
            }
        }
    }
    catch (const std::exception &e)
    {
        // Handle error
    }

    return files;
}

std::vector<std::string> FileManager::listAudioFiles(const std::string &directory, bool recursive)
{
    std::vector<std::string> audioFiles;

    try
    {
        if (recursive)
        {
            for (const auto &entry : fs::recursive_directory_iterator(directory))
            {
                if (entry.is_regular_file() && isAudioFile(entry.path().string()))
                {
                    audioFiles.push_back(entry.path().string());
                }
            }
        }
        else
        {
            for (const auto &entry : fs::directory_iterator(directory))
            {
                if (entry.is_regular_file() && isAudioFile(entry.path().string()))
                {
                    audioFiles.push_back(entry.path().string());
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        // Handle error
    }

    return audioFiles;
}

bool FileManager::fileExists(const std::string &filepath)
{
    return fs::exists(filepath);
}

std::string FileManager::getExtension(const std::string &filepath)
{
    fs::path path(filepath);
    std::string ext = path.extension().string();

    // Remove the dot and convert to lowercase
    if (!ext.empty() && ext[0] == '.')
    {
        ext = ext.substr(1);
    }
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    return ext;
}

std::string FileManager::getFilename(const std::string &filepath)
{
    fs::path path(filepath);
    return path.stem().string();
}

std::string FileManager::getDirectory(const std::string &filepath)
{
    fs::path path(filepath);
    return path.parent_path().string();
}

bool FileManager::isAudioFile(const std::string &filepath)
{
    std::string ext = getExtension(filepath);
    auto supportedExts = getSupportedExtensions();

    return std::find(supportedExts.begin(), supportedExts.end(), ext) != supportedExts.end();
}

std::vector<std::string> FileManager::getSupportedExtensions()
{
    return {
        "mp3", "wav", "flac", "ogg", "m4a", "aac",
        "wma", "opus", "ape", "alac"};
}
