#include "headers/FileSystem.h"
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include "headers/Functions.h"

bool FileSystem::isFileExist(const string filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

bool FileSystem::isDirectoryExist(const string directoryname) {
    return isFileExist(directoryname);
}

string FileSystem::readFile(const string filename) {
    string data;
    if (isFileExist(filename))
    {
        auto ss = ostringstream{};
        ifstream inputFile(filename);
        ss << inputFile.rdbuf();
        data = ss.str();
    }
    return data;
}

void FileSystem::writeFile(const string filename, const string data, const bool overwrite) {
    if (!data.empty())
    {
        ofstream outputFile;
        if (!overwrite && isFileExist(filename))
        {
            outputFile.open(filename, STD::ios_base::app);
        }
        outputFile.write(data.data(), data.size());
    }
}

list<IFileInfo> FileSystem::readDirectory(const string directoryname) {
    list<IFileInfo> files;
    cout << directoryname << endl;
    if (isDirectoryExist(directoryname)) {
        DIR *dr;
        struct dirent *en;
        dr = opendir(directoryname.c_str());
        if (dr) {
            while ((en = readdir(dr)) != NULL) {
                IFileInfo fileinfo = getFileInfo(resolvePath(directoryname + "/" + en->d_name));
                if (!Functions::equal(fileinfo.basename, ".") && !Functions::equal(fileinfo.basename, "..")) {
                    files.push_front(fileinfo);
                }
            }
            closedir(dr); // close all directory
        }
    }
    return files;
}

EPlatformType FileSystem::getPlatformType() {
    #ifdef _WIN32
    return EPlatformType::WIN_32;
    #elif _WIN64
    return EPlatformType::WIN_64;
    #elif __APPLE__ || __MACH__
    return EPlatformType::MAC_OSX;
    #elif __linux__
    return EPlatformType::LINUX;
    #elif __FreeBSD__
    return EPlatformType::FREE_BSD;
    #elif __unix || __unix__
    return EPlatformType::UNIX;
    #else
    return EPlatformType::OTHER;
    #endif
}

bool FileSystem::isWindows() {
    return getPlatformType() == EPlatformType::WIN_32 || getPlatformType() == EPlatformType::WIN_64;
}

bool FileSystem::isMacOSX() {
    return getPlatformType() == EPlatformType::MAC_OSX;
}

bool FileSystem::isLinux() {
    return getPlatformType() == EPlatformType::LINUX;
}

bool FileSystem::isFreeBSD() {
    return getPlatformType() == EPlatformType::FREE_BSD;
}

bool FileSystem::isUnix() {
    return getPlatformType() == EPlatformType::UNIX;
}

string FileSystem::resolvePath(const string path) {
    if (isWindows()) {
        return Functions::replaceAll(path, "/", "\\");
    } else if (isLinux() || isMacOSX() || isUnix()) {
        return Functions::replaceAll(path, "\\", "/");
    }
    return path;
}

string FileSystem::getCurrentDir() {
    char currentDir[256];
    getcwd(currentDir, 256);
    return currentDir;
}

IFileInfo FileSystem::getFileInfo(const string filepath) {
    IFileInfo info;
    char seperator = '/';
    if (isWindows()) {
        seperator = '\\';
    }
    // Get last dot position
    size_t dotPos = filepath.rfind('.');
    info.extension = dotPos != string::npos ? filepath.substr(dotPos + 1, filepath.size()) : "";

    // Get last separator position
    size_t sepPos = filepath.rfind(seperator);
    info.basename = sepPos != std::string::npos ? filepath.substr(sepPos + 1, filepath.size()) : filepath;
    info.basenameWithoutExtension = info.basename;

    if (!info.extension.empty()) {
         // Get last dot position
        dotPos = info.basenameWithoutExtension.rfind('.');
        info.basenameWithoutExtension = info.basenameWithoutExtension.substr(0, dotPos);
    }
    info.filename = filepath;
    info.dirname = Functions::replaceAll(filepath, seperator + info.basename, "");
    return info;
}