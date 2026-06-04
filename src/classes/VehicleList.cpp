#include "../include/classes/VehicleList.hpp"
#include <algorithm>
#include <cctype>

VehicleList::VehicleList(Database *conn, Logger *logger)
    : conn(conn), logger(logger) {}

bool VehicleList::isSelectQuery(const std::string &query) const {
  std::string normalized;
  normalized.reserve(query.size());

  for (unsigned char ch : query) {
    if (!std::isspace(ch)) {
      normalized.push_back(static_cast<char>(std::toupper(ch)));
    }
  }

  return normalized.rfind("SELECT", 0) == 0;
}

void VehicleList::initList(const std::string &query) {
  vehicleList.clear();
  errors.clear();

  if (query.empty()) {
    errors.push_back("Query cannot be empty.");
    return;
  }

  if (!isSelectQuery(query)) {
    errors.push_back("Only SELECT queries are allowed.");
    if (logger) {
      logger->log(LogLevel::Warning, "VehicleList blocked non-SELECT query.");
    }
    return;
  }

  auto mapVehicle = [](sqlite3_stmt *stmt) -> VehicleSummary {
    VehicleSummary vehicle;
    const unsigned char *brand = sqlite3_column_text(stmt, 0);
    const unsigned char *model = sqlite3_column_text(stmt, 1);
    const unsigned char *year = sqlite3_column_text(stmt, 2);
    const unsigned char *color = sqlite3_column_text(stmt, 3);

    vehicle.brand = brand ? reinterpret_cast<const char *>(brand) : "";
    vehicle.model = model ? reinterpret_cast<const char *>(model) : "";
    vehicle.year = year ? reinterpret_cast<const char *>(year) : "";
    vehicle.color = color ? reinterpret_cast<const char *>(color) : "";
    return vehicle;
  };

  vehicleList = conn->fetch<VehicleSummary>(query, mapVehicle);

  if (vehicleList.empty() && logger) {
    logger->log(LogLevel::Warning,
                "VehicleList returned an empty list for provided query.");
  }
}

const std::vector<VehicleSummary> &VehicleList::getList() const {
  return vehicleList;
}

const std::vector<std::string> &VehicleList::getErrors() const { return errors; }