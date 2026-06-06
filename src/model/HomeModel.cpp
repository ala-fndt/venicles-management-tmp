#include "../include/model/HomeModel.hpp"

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
