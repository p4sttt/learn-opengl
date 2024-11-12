#include "Logger.hpp"

#include <iostream>

void Logger::debug(const std::string &message, const char *file) {
    std::cout << "[DEBUG] at " << file << ": " << message << std::endl;
}

void Logger::info(const std::string &message, const char *file) {
    std::cout << "[INFO] at " << file << ": " << message << std::endl;
}

void Logger::error(const std::string &message, const char *file) {
    std::cerr << "[ERROR] at " << file << ": " << message << std::endl;
}