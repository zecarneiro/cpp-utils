#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Namespace.h"
#include "FileSystem.h"
using namespace STD;

class Console {
    public:
        static void clearCin();
        static int getOnlyInteger(const string messageError);
        static string getLine();
        static string exec(const string cmd);
        static void execRealTime(const string cmd);
        static void clear();
};

#endif // __CONSOLE_H__