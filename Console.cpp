#include "headers/Console.h"
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
using std::array;
using std::unique_ptr;

void Console::clearCin() {
    if (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cin.ignore();
    }
}

string Console::getLine() {
    string line;
    getline(cin, line);
    clearCin();
    return line;
}

/**
 * Get only number from cin
 * @arg errorMessage Message to print if invalid incert
 */
int Console::getOnlyInteger(const string messageError) {
	int integer;
	cin >> integer;

	// ask when user not introduce integer
    while(cin.fail()) {
        clearCin();
        cout << messageError;
        cin >> integer;
    }
    clearCin();
    return integer;
}

string Console::exec(const string cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void Console::execRealTime(const string cmd) {
    system(cmd.c_str());
}

void Console::clear() {
    if (FileSystem::isWindows()) {
        execRealTime("cls");
    } else if (FileSystem::isLinux() || FileSystem::isMacOSX() || FileSystem::isUnix()) {
        execRealTime("clear");
    }
}