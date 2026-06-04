#ifndef VEHICLELIST_HPP
#define VEHICLELIST_HPP

#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"
#include "../include/model/VehicleSummary.hpp"
#include <string>
#include <vector>

class VehicleList {
private:
  Database *conn;
  Logger *logger;
  std::vector<VehicleSummary> vehicleList;
  std::vector<std::string> errors;

  bool isSelectQuery(const std::string &query) const;

public:
  VehicleList(Database *conn, Logger *logger);

  void initList(const std::string &query);
  const std::vector<VehicleSummary> &getList() const;
  const std::vector<std::string> &getErrors() const;
};

#endif // !VEHICLELIST_HPP