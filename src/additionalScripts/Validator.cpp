#include "../../include/additionalScripts/Validator.hpp"
#include <wx/textctrl.h>

Validator::Validator(Logger &loggerInstance) : logger(loggerInstance) {};

Validator::~Validator() = default;

bool Validator::validateEmail(const std::string &email) {
  const std::regex emailPattern(R"(^[^\s@]+@[^\s@.]+\.[^\s@]{2,}$)");

  if (!std::regex_match(email, emailPattern)) {
    errors.push_back("Wrong email format.");
    logger.log(LogLevel::Error, "Wrong email format of email: " + email);
    return false;
  };

  logger.log(LogLevel::Info, "Succesful email validation.");
  return true;
}

bool Validator::validatePassword(const std::string &password) {
  // Warunek 1) -> Wymagany minimalny rozmiar dla hasła: 13 znaków
  if (password.length() < 13) {
    errors.push_back("Password is too short");
    logger.log(LogLevel::Error, "Password is too short.");
    return false;
  }

  // Warunek 2) -> Hasło musi zawierać przynajmniej jedną cyfrę
  if (!any_of(password.begin(), password.end(),
              [](unsigned char c) { return isdigit(c); })) {
    errors.push_back("Password must contain at least one digit.");
    logger.log(LogLevel::Error, "Password must contain at least one digit.");
    return false;
  }

  // Warunek 3) -> Hasło musi zawierać przynajmniej jedną dużą literę
  if (!any_of(password.begin(), password.end(),
              [](unsigned char c) { return isupper(c); })) {
    errors.push_back("Password must contain at least one uppercase letter.");
    logger.log(LogLevel::Error,
               "Password must contain at least one uppercase letter.");
    return false;
  }

  logger.log(LogLevel::Info, "Successful password validation.");
  return true;
}

bool Validator::checkEmpty(const std::string &value) {
  if (value.empty()) {
    errors.push_back("Value can't be empty.");
    logger.log(LogLevel::Error, "Value can't be empty.");
    return true;
  }
  return false;
}

void Validator::clearFields(const std::vector<wxTextCtrl *> &fields) {
  for (auto *field : fields) {
    if (field) {
      field->Clear();
    }
  }
  logger.log(LogLevel::Info, "Pola tekstowe zostały wyczyszczone.");
}

std::vector<std::string> Validator::getErrors() {
  std::vector<std::string> tmpErr = errors;
  errors.clear();
  return tmpErr;
};
