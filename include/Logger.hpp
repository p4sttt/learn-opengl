#include <string>

#ifndef LOGGER_HPP
#define LOGGER_HPP

namespace Logger {

void debug(const std::string &message, const char *file);
void info(const std::string &message, const char *file);
void warn(const std::string &message, const char *file);
void error(const std::string &message, const char *file);

}; // namespace Logger

#endif

#define LOG(x) Logger::debug(x, __FILE__)
#define LOG_INFO(x) Logger::info(x, __FILE__)
#define LOG_WARN(x) Logger::warn(x, __FILE__)
#define LOG_ERROR(x) Logger::error(x, __FILE__)