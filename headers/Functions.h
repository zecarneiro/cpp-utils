#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Namespace.h"
#include "../enums/ETrimType.h"
using namespace STD;

class Functions {
    public:
        static bool contain(const string data, const string dataCompare);
        static bool equal(const string data, const string dataCompare);
        static string trim(const string data, const string characters = " \n\r\t", const ETrimType typeTrim = ETrimType::ALL);
        static string replaceAll(const string data, const string search, const string replace);

        template <class T, class U>
        static bool existOnMapByKey(const map<T, U> data, const T key) {
            auto search = data.find(key);
            if (search != data.end()) {
                return true;
            }
            return false;
        }

        template <class T>
        static bool inList(const list<T> data, const T toSearch) {
            return (find(data.begin(), data.end(), toSearch) != data.end()) ? true : false;
        }
};

#endif // FUNCTIONS_H