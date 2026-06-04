#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "Logger.hpp"
#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <vector>

class wxTextCtrl;

class Validator {
private:
  Logger &logger;
  std::vector<std::string> errors;

public:
  Validator(Logger &loggerInstance);
  ~Validator();

  bool validateEmail(const std::string &email);

  bool validatePassword(const std::string &password);

  bool checkEmpty(const std::string &value);

  void clearFields(const std::vector<wxTextCtrl *> &fields);

  std::vector<std::string> getErrors();
};

#endif
