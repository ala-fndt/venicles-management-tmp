#include "../include/model/LoginModel.hpp"
#include "../include/classes/User.hpp"
#include <vector>

LoginModel::LoginModel(Database *conn, Logger *logger)
    : conn(conn), logger(logger) {
  errors.clear();
}

LoginModel::~LoginModel() = default;

std::vector<std::string> LoginModel::getErrors() {
  std::vector<std::string> tmpErr = this->errors;
  this->errors.clear();
  return tmpErr;
}

std::optional<User> LoginModel::returnUserData(const std::string &email) {
  auto mapToUser = [](sqlite3_stmt *stmt) -> User {
    User user;
    user.setId(static_cast<int>(sqlite3_column_int(stmt, 0)));
    user.setName((const char *)sqlite3_column_text(stmt, 1));
    user.setSurname((const char *)sqlite3_column_text(stmt, 2));
    user.setEmail((const char *)sqlite3_column_text(stmt, 3));
    user.setAdminPermission(static_cast<bool>(sqlite3_column_int(stmt, 4)));
    user.setAccountBalance(sqlite3_column_int(stmt, 5));
    return user;
  };

  std::string sql =
      "SELECT id, name, surname, email, isAdmin, accountBalance FROM users "
      "WHERE email = '" + email + "' LIMIT 1;";

  std::vector<User> users = this->conn->fetch<User>(sql, mapToUser);

  if (users.empty()) {
    logger->log(LogLevel::Critical, "User are empty");
    return std::nullopt;
  }

  return users[0];
}

bool LoginModel::checkUserExist(const std::string &email) {
  std::vector<User> user;
  errors.clear();

  if (email.empty()) {
    errors.push_back("Empty email");
    return false;
  }

  auto mapToUser = [](sqlite3_stmt *stmt) -> User {
    User user;
    user.setEmail((const char *)sqlite3_column_text(stmt, 0));

    return user;
  };

  std::string sql = "SELECT email FROM users WHERE email = '" + email + "';";

  user = this->conn->fetch<User>(sql, mapToUser);

  if (user.empty()) {
    logger->log(LogLevel::Error, "User doesnt exist");
    errors.push_back("User doesnt exist. Please register");

    return false;
  }
  return true;
}

bool LoginModel::checkPassword(const std::string &password,
                               const std::string &email) {
  std::vector<User> user;
  errors.clear();

  auto mapToUser = [](sqlite3_stmt *stmt) -> User {
    User user;
    user.setPassword((const char *)sqlite3_column_text(stmt, 0));
    return user;
  };

  std::string sql = "SELECT password FROM users WHERE email = '" + email + "';";

  user = this->conn->fetch<User>(sql, mapToUser);

  if (user.empty()) {
    logger->log(LogLevel::Error, "User doesnt exist");
    errors.push_back("User doesnt exist");

    return false;
  }

  if (password != user[0].getPassword()) {

    // TODO: odszyfrowanie hasla
    logger->log(LogLevel::Error, "Passwords are not same");

    errors.push_back("Passwords are not same");

    return false;
  }

  logger->log(LogLevel::Error, "Password are correct");

  return true;
};
