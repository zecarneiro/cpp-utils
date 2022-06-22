#include "headers/Functions.h"

bool Functions::contain(string data, string dataCompare) {
    return data.find(dataCompare) != string::npos;
}

bool Functions::equal(string data, string dataCompare) {
    return data.compare(dataCompare) == 0;
}

string Functions::replaceAll(string data, string toSearch, string replaceStr) {
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceStr.size());
    }
    return data;
}

string Functions::trim(string data, string characters, ETrimType trimType) {
    if (trimType == ETrimType::LEFT || trimType == ETrimType::ALL) {
        data.erase(0, data.find_first_not_of(characters.c_str()));
    }

    if (trimType == ETrimType::RIGHT || trimType == ETrimType::ALL) {
        data.erase(data.find_last_not_of(characters.c_str()) + 1);
    }
    return data;
}