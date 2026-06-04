#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../include/additionalScripts/Logger.hpp"
#include <functional>
#include <iostream>
#include <sqlite3.h>
#include <vector>

class Database {
private:
  std::string const path = "src/database";
  const char *nazwaDB = "database.db";
  sqlite3 *db = nullptr;

  std::string errorLog(std::string &message, std::vector<std::string> &errors);
  void checkConnection();

public:
  Logger *logger;
  std::vector<std::string> errors;
  std::vector<std::string> tables;
  std::vector<std::string> insertions;

  Database(Logger *logger);
  ~Database();

  void initDatabase();
  void executeQuery(const std::string &query);

  // metoda pisana z chatem (nie miałem absolutnie pojęcia jak zrobić fetch i
  // konwersje na klasy)
  template <typename T>
  std::vector<T> fetch(const std::string &sql,
                       std::function<T(sqlite3_stmt *)> mapper) {
    this->checkConnection();
    std::vector<T> results;
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      return results;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
      results.push_back(mapper(stmt));
    }

    sqlite3_finalize(stmt);
    return results;
  }
};

#endif // !DATABASE_HPP
