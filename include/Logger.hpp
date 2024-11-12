#include <string>

#ifndef LOGGER_HPP
#define LOGGER_HPP

class Logger {
  public:
    static void debug(const std::string &message, const char *file);

    static void info(const std::string &message, const char *file);

    static void error(const std::string &message, const char *file);
};

#define LOG(x) Logger::debug(x, __FILE__)
#define LOG_INFO(x) Logger::info(x, __FILE__)
#define LOG_ERROR(x) Logger::error(x, __FILE__)

#endif