#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "FilmArray.h"
#include <string>

class FileOperations {
public:
    static void saveToFile(const std::string& filename, const FilmArray& array);
    static FilmArray loadFromFile(const std::string& filename);
};

#endif
