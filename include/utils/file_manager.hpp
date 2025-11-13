#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>

class FileManager
{
public:
    // Directory operations
    static std::vector<std::string> listFiles(const std::string &directory);
    static std::vector<std::string> listAudioFiles(const std::string &directory, bool recursive = false);

    // File operations
    static bool fileExists(const std::string &filepath);
    static std::string getExtension(const std::string &filepath);
    static std::string getFilename(const std::string &filepath);
    static std::string getDirectory(const std::string &filepath);

    // Audio file detection
    static bool isAudioFile(const std::string &filepath);
    static std::vector<std::string> getSupportedExtensions();

private:
    FileManager() = default;
};

#endif // FILE_MANAGER_HPP
