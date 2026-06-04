#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

enum class LogLevel { Debug, Info, Warning, Error, Critical };

class Logger {
private:
  std::ofstream logFile;
  std::string levelToString(LogLevel level);

public:
  Logger();
  ~Logger();

  void log(LogLevel level, const std::string &message);
};

#endif // LOGGER_HPP
