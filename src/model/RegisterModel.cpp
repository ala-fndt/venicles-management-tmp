#include "../include/model/RegisterModel.hpp"
#include "../include/classes/User.hpp"

RegisterModel::RegisterModel(Database *conn, Logger *logger)
    : conn(conn), logger(logger) {
  errors.clear();
}

RegisterModel::~RegisterModel() = default;

bool RegisterModel::checkUserExists(const std::string &email) {
  errors.clear();

  auto mapToUser = [](sqlite3_stmt *stmt) -> User {
    User user;
    user.setEmail((const char *)sqlite3_column_text(stmt, 0));
    return user;
  };

  std::string sql =
      "SELECT email FROM users WHERE email = '" + email + "' LIMIT 1;";
  std::vector<User> users = conn->fetch<User>(sql, mapToUser);

  if (!users.empty()) {
    errors.push_back("A user with this email address already exists.");
    logger->log(LogLevel::Warning,
                "Registration attempt for an existing email: " + email);
    return true;
  }
  return false;
}

bool RegisterModel::registerUser(const std::string &name,
                                 const std::string &surname,
                                 const std::string &email,
                                 const std::string &password) {
  errors.clear();

  std::string sql =
      "INSERT INTO users (name, surname, email, password, isAdmin) VALUES ('" +
      name + "', '" + surname + "', '" + email + "', '" + password +
      "', 'false');";

  conn->executeQuery(sql);

  logger->log(LogLevel::Info, "Registered a new user: " + email);
  return true;
}

std::vector<std::string> RegisterModel::getErrors() {
  std::vector<std::string> tmp = errors;
  errors.clear();
  return tmp;
}
