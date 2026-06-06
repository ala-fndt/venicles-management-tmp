#include "../include/database/Database.hpp"
#include "../include/additionalScripts/Logger.hpp"

Database::Database(Logger *logger) : logger(logger) {};

Database::~Database() {
  if (db) {
    sqlite3_close(db);
    db = nullptr;
  }
};

void Database::checkConnection() {
  if (db != nullptr) {
    return;
  }

  if (sqlite3_open(nazwaDB, &db) != SQLITE_OK) {
    logger->log(LogLevel::Critical, "Nie udalo sie otworzyc bazy: " +
                                        std::string(sqlite3_errmsg(db)));
    sqlite3_close(db);
    db = nullptr;
  }
}

std::string Database::errorLog(std::string &message,
                               std::vector<std::string> &errors) {

  int i = 1;
  for (const std::string &error : errors) {
    message += std::to_string(i) + ". " + error + "\n";
    i++;
  }

  return message;
}

void Database::initDatabase() {
  char *messageError;
  bool success = true;

  this->checkConnection();

  // INFO: default tables on database init
  tables = {
      "CREATE TABLE IF NOT EXISTS users("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "name           TEXT              NOT NULL, "
      "surname        TEXT              NOT NULL, "
      "email          TEXT    UNIQUE    NOT NULL, "
      "password       TEXT              NOT NULL, "
      "isAdmin        BOOL              NOT NULL, "
      "accountBalance INTEGER           NOT NULL);",

      "CREATE TABLE IF NOT EXISTS vehicle("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "vin            TEXT  UNIQUE    NOT NULL, "
      "brand          TEXT            NOT NULL, "
      "model          TEXT            NOT NULL, "
      "year           TEXT            NOT NULL, "
      "color          TEXT            NOT NULL, "
      "fuelType       TEXT            NOT NULL, "
      "technicalStatus TEXT           NOT NULL, "
      "mileage        INTEGER         NOT NULL, "
      "pricePerDay    INTEGER         NOT NULL, "

      // INFO: specyfikacja dla klas dziedziczacych
      "numberOfSeats  INTEGER,"
      "engineCapacity INTEGER,"
      "handleBarsType TEXT,"
      "maxCargoWeight INTEGER,"
      "numberOfAxles  INTEGER);",

      "CREATE TABLE IF NOT EXISTS userVehicle("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "idUser         INTEGER    NOT NULL, "
      "idVehicle      INTEGER    NOT NULL, "
      "date           TEXT       NOT NULL, "
      "UNIQUE(idUser, idVehicle));",

      "CREATE TABLE IF NOT EXISTS rentalHistory("
      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "idUser         INTEGER            NOT NULL, "
      "idVehicle      INTEGER            NOT NULL, "
      "date           TEXT               NOT NULL, "
      "UNIQUE(idUser, idVehicle));",
  };

  // INFO: default isertions on database init
  insertions = {
      "INSERT OR IGNORE INTO users (name, surname, email, password, isAdmin, accountBalance) "
      "VALUES('admin', 'admin', 'admin@example.com', '123', 1, 99999999);",

      "INSERT OR IGNORE INTO users (name, surname, email, password, isAdmin, accountBalance) "

      "VALUES('Jan', 'Kowalski', 'JanK@example.com', '123', 0, 15700);",

      "INSERT OR IGNORE INTO vehicle (brand, vin, model, year, color, "
      "fuelType, technicalStatus, mileage, pricePerDay, numberOfSeats) "
      "VALUES('Toyota', 'JTDBR32E720054781' ,'Yaris', '2006', 'RED', "
      "'GAS', 'Good', 4000, 170, 2);",

      "INSERT OR IGNORE INTO vehicle (brand, vin, model, year, color, "
      "fuelType, technicalStatus, mileage, pricePerDay, numberOfSeats) "
      "VALUES('BMW', 'WBA3A5C57DF357921' ,'x5', '2007', 'WHITE', 'DIESEL', "
      "'Good', 2000, 170, 4);",

      "INSERT OR IGNORE INTO vehicle (brand, vin, model, year, color, "
      "fuelType, technicalStatus, mileage, pricePerDay, numberOfSeats) "
      "VALUES('BMW', 'WBA3A5C57DF354321' ,'x5', '2007', 'WHITE', 'DIESEL', "
      "'Good', 2000, 170, 4);",

      "INSERT INTO vehicle (vin, brand, model, year, color,fuelType, "
      "technicalStatus, mileage, pricePerDay, handleBarsType, engineCapacity) VALUES "
      "('JH2SC59057M123456','Honda','CBR600RR','2021','Red','Petrol','Valid', "
      "18500, 125, 'Clip-on',599);",

      "INSERT INTO vehicle (vin, brand, model, year, color,fuelType, "
      "technicalStatus, mileage, pricePerDay, numberOfSeats, engineCapacity, maxCargoWeight, "
      "numberOfAxles) VALUES "
      "('WDB9340321L987654','Mercedes-Benz','Actros','2019','White','Diesel','"
      "Valid', 420000, 450, 2, 12809, 18000, 3);",

      "INSERT OR IGNORE INTO userVehicle (idUser, idVehicle, date) "
      "VALUES(1, 1, '00-00-0000');",

      "INSERT OR IGNORE INTO rentalHistory (idUser, idVehicle, date) "
      "VALUES(1, 1, '00-00-0000');",
  };

  for (const std::string &sql : tables) {
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError) !=
        SQLITE_OK) {
      success = false;
      errors.push_back(std::string(messageError));
      sqlite3_free(messageError);
    }
  }

  for (const std::string &sql : insertions) {
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messageError) !=
        SQLITE_OK) {
      success = false;
      errors.push_back(std::string(messageError));
      sqlite3_free(messageError);
    }
  }

  if (!success) {
    std::string mess = "Blad tworzenia bazy danych: ";

    std::string messageErrors = Database::errorLog(mess, errors);

    logger->log(LogLevel::Critical, messageErrors);
  } else {
    logger->log(LogLevel::Info,
                "Baza danych utworzona pod nazwa: " + (std::string)nazwaDB);
  }
}

void Database::executeQuery(const std::string &query) {
  this->checkConnection();
  if (!db) {
    return;
  }

  char *messageError = nullptr;
  if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &messageError) !=
      SQLITE_OK) {
    errors.push_back(std::string(messageError));
    sqlite3_free(messageError);
  } else {
    logger->log(LogLevel::Info, "Wykonano: " + query.substr(0, 6));
  }
}
