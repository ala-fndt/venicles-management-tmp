#include "../include/model/HomeModel.hpp"
#include "../include/classes/Session.hpp"

HomeModel::HomeModel(Database *conn, Logger *logger)
    : conn(conn), logger(logger), vehicleList(conn, logger) {}

int HomeModel::getVehicleCount() {
  return static_cast<int>(getVehicles().size());
}

std::vector<VehicleSummary> HomeModel::getVehicles() {
  return getVehiclesByQuery(
  "SELECT id, brand, model, year, color FROM vehicle ORDER BY id;");
}

std::vector<VehicleSummary>
HomeModel::getVehiclesByQuery(const std::string &query) {
  vehicleList.initList(query);
  std::vector<VehicleSummary> vehicles = vehicleList.getList();

  if (vehicles.empty() && logger) {
    logger->log(LogLevel::Warning, "No vehicles in vehicle table");
  }

  return vehicles;
}

const std::vector<std::string> &HomeModel::getVehicleErrors() const {
  return vehicleList.getErrors();
}

Database* HomeModel::getDatabase() {
  return conn;
}

double HomeModel::getAccountBalance() {
  if(!conn) {
    return 0.0;
  }

  int userId = Session::getInstance().getUserId();
  if(userId < 0) {
    return 0.0;
  }

  std::string sql = "SELECT accountBalance FROM users WHERE id = " + std::to_string(userId) + ";";
  
   auto mapper = [](sqlite3_stmt* stmt) -> int {
        // accountBalance jest typu INTEGER, więc pobieramy jako int i konwertujemy
        return sqlite3_column_int(stmt, 0);
    };

    std::vector<int> result = conn->fetch<int>(sql, mapper);
    
    if (result.empty()) {
        if (logger) {
            logger->log(LogLevel::Warning, "Could not fetch account balance for user ID: " + std::to_string(userId));
        }
        return 0.0;
    }

    return static_cast<double>(result.front()) / 100.0;
}