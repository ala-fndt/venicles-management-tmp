#include "../../include/model/UserPageModel.hpp"
#include "../../include/classes/Session.hpp"

UserPageModel::UserPageModel(Database *database, Logger *logger)
    : database(database), logger(logger) {}

UserPageModel::~UserPageModel() {}

bool UserPageModel::showAdminSettings()
{
  if (!Session::getInstance().getAdmin())
  {
    logger->log(LogLevel::Info, "No access");
    return false;
  }

  logger->log(LogLevel::Info, "User " + Session::getInstance().getName() +
                                  " jest administratorem");
  return true;
}

std::vector<Vehicle> UserPageModel::getUserVehicles()
{
  std::vector<Vehicle> vehicles;

  std::string userId = std::to_string(Session::getInstance().getUserId());

  auto mapToVehicle = [](sqlite3_stmt *stmt) -> Vehicle
  {
    Vehicle vehicle;
    vehicle.setId((const int)sqlite3_column_int(stmt, 0));
    vehicle.setBrand((const char *)sqlite3_column_text(stmt, 1));
    vehicle.setModel((const char *)sqlite3_column_text(stmt, 2));
    vehicle.setYear((const char *)sqlite3_column_text(stmt, 3));
    vehicle.setColor((const char *)sqlite3_column_text(stmt, 4));

    return vehicle;
  };

  // WARNING: NIE RUSZAĆ
  std::string sql =
      "SELECT vehicle.id, vehicle.brand, vehicle.model, vehicle.year, "
      "vehicle.color FROM userVehicle "
      "JOIN users ON userVehicle.idUser = users.id "
      "JOIN vehicle ON userVehicle.idVehicle = vehicle.id "
      "WHERE users.id = " +
      userId + ";";

  vehicles = database->fetch<Vehicle>(sql, mapToVehicle);

  if (vehicles.empty())
  {
    logger->log(LogLevel::Warning, "Dane nie zostały pobrane");
  }

  for (Vehicle vehicle : vehicles)
  {
    std::cout << vehicle.getModel() << std::endl;
  }

  return vehicles;
}

std::vector<VehicleSummary> UserPageModel::getRentalHistory()
{
  std::string userId = std::to_string(Session::getInstance().getUserId());

  auto mapToSummary = [](sqlite3_stmt *stmt) -> VehicleSummary
  {
    VehicleSummary summary;
    summary.brand = (const char *)sqlite3_column_text(stmt, 0);
    summary.model = (const char *)sqlite3_column_text(stmt, 1);
    summary.year = (const char *)sqlite3_column_text(stmt, 2);
    summary.color = (const char *)sqlite3_column_text(stmt, 3);
    return summary;
  };

  std::string sql =
      "SELECT vehicle.brand, vehicle.model, vehicle.year, vehicle.color "
      "FROM rentalHistory "
      "JOIN vehicle ON rentalHistory.idVehicle = vehicle.id "
      "WHERE rentalHistory.idUser = " + userId + " ORDER BY rentalHistory.id DESC LIMIT 10;";

  std::vector<VehicleSummary> history = database->fetch<VehicleSummary>(sql, mapToSummary);

  return history;
}

bool UserPageModel::addVehicle(const std::string &vin, const std::string &brand,
                               const std::string &model, const std::string &year,
                               const std::string &color)
{
  std::string userId = std::to_string(Session::getInstance().getUserId());
  std::string sqlVehicle = "INSERT INTO vehicle (vin, brand, model, year, color) VALUES ('" +
                           vin + "', '" + brand + "', '" + model + "', '" + year + "', '" + color + "');";
  database->executeQuery(sqlVehicle);

  std::string sqlLink = "INSERT INTO userVehicle (idUser, idVehicle, date) VALUES (" +
                        userId + ", last_insert_rowid(), date('now'));";
  database->executeQuery(sqlLink);
  return true;
}
