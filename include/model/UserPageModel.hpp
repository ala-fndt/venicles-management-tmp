#ifndef USER_PAGE_MODEL_HPP
#define USER_PAGE_MODEL_HPP

#include "../include/additionalScripts/Logger.hpp"
#include "../include/classes/Router.hpp"
#include "../include/classes/Vehicle.hpp"
#include "../include/model/VehicleSummary.hpp"
#include "../include/database/Database.hpp"

class UserPageModel {
private:
  Router *router;
  Database *database;
  Logger *logger;

  bool isAdmin = false;
  std::vector<Vehicle *> userVehicles;

  bool checkAdmin();

public:
  UserPageModel(Database *database, Logger *logger);
  ~UserPageModel();

  bool showAdminSettings();
  std::vector<Vehicle> getUserVehicles();
  std::vector<VehicleSummary> getRentalHistory();
  bool addVehicle(const std::string& vin, 
                  const std::string& brand, 
                  const std::string& model, 
                  const std::string& year, 
                  const std::string& color);
};

#endif // !USER_PAGE_MODEL_HPP
