#ifndef USER_PAGE_MODEL_HPP
#define USER_PAGE_MODEL_HPP

#include <string>
#include <vector>
#include "../../include/database/Database.hpp"
#include "../../include/additionalScripts/Logger.hpp"
#include "../../include/classes/VehicleList.hpp"

class UserPageModel {
public:
    UserPageModel(Database *db, Logger *logger);
    ~UserPageModel();

    bool addVehicle(const std::string& vin, const std::string& brand, const std::string& model, 
                    const std::string& year, const std::string& color, const std::string& fuelType, 
                    const std::string& status, int mileage, int seats, int engine, 
                    const std::string& handle, int cargo, int axles);

    std::vector<VehicleSummary> getRentalHistory();

private:
    Database *_db;
    Logger *_logger;
};

#endif