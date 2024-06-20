#include "CSVReader.hpp"
#include <sstream>
#include <iostream>

CSVReader::CSVReader(const std::string& filename) : file(filename) {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    parseHeader();
}

void CSVReader::parseHeader() {
    std::string headerLine;
    if (std::getline(file, headerLine)) {
        std::stringstream ss(headerLine);
        std::string column;
        size_t index = 0;
        while (std::getline(ss, column, ',')) {
            header[column] = index++;
        }
    }
}

bool CSVReader::parseLine() {
    if (std::getline(file, currentLine)) {
        std::stringstream ss(currentLine);
        std::string value;
        currentRow.clear();

        while (std::getline(ss, value, ',')) {
            currentRow.push_back(value);
        }

        // Fügt zusätzliche leere Felder hinzu, falls notwendig
        if (currentLine.back() == ',') {
            currentRow.push_back("");
        }

        return true;
    }
    return false;
}


std::string CSVReader::getField(const std::string& key, const std::string& defaultValue) {
    auto it = header.find(key);
    if (it != header.end() && it->second < currentRow.size() && !currentRow[it->second].empty()) {
        return currentRow[it->second];
    }
    return defaultValue;
}

bool CSVReader::next() {
    return parseLine();
}

bool CSVReader::hasNext() const {
    return !file.eof();
}

void CSVReader::reset() {
    file.clear();
    file.seekg(0);
    parseHeader();
}
