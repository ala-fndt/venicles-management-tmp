#ifndef LOGIN_MODEL_HPP
#define LOGIN_MODEL_HPP

#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"
#include "./classes/User.hpp"
#include <optional>
#include <string>

/**
 * @class LoginModel
 * @brief Odpowiada za logowanie uzytkownika
 */
class LoginModel {

private:
  Database *conn;
  Logger *logger;

  std::vector<std::string> errors;

public:
  LoginModel(Database *conn, Logger *logger);
  ~LoginModel();

  bool getLoginFlag();

  std::optional<User> returnUserData(const std::string &email);
  bool checkUserExist(const std::string &email);
  bool checkPassword(const std::string &password, const std::string &email);

  std::vector<std::string> getErrors();
};

#endif // !LOGIN_MODEL_HPP
