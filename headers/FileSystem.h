#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "Namespace.h"
#include "../enums/EPlatformType.h"
#include "../interfaces/IFileInfo.h"
using namespace STD;

class FileSystem {
    public:
        static bool isFileExist(const string filename);
        static bool isDirectoryExist(const string directoryname);
        static string readFile(const string filename);
        static void writeFile(const string filename, const string data, const bool overwrite = true);
        static list<IFileInfo> readDirectory(const string directoryname);
        static EPlatformType getPlatformType();
        static bool isWindows();
        static bool isMacOSX();
        static bool isLinux();
        static bool isFreeBSD();
        static bool isUnix();
        static string resolvePath(const string path);
        static string getCurrentDir();
        static IFileInfo getFileInfo(const string filepath);
};

#endif // __FILESYSTEM_H__