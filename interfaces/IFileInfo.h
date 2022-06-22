#ifndef __IFILEINFO_H__
#define __IFILEINFO_H__

#include "../headers/Namespace.h"
using namespace STD;

struct IFileInfo {
    string basename;
    string filename;
    string dirname;
    string extension;
    string basenameWithoutExtension;
};
#endif // __IFILEINFO_H__