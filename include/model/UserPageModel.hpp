#ifndef USER_PAGE_MODEL_HPP
#define USER_PAGE_MODEL_HPP

#include "../include/additionalScripts/Logger.hpp"
#include "../include/classes/Router.hpp"
#include "../include/classes/Vehicle.hpp"
#include "../include/model/VehicleSummary.hpp"
#include "../include/database/Database.hpp"
#include <vector>
#include <memory>

class UserPageModel {
private:
    Database *database;
    Logger *logger;

public:
    UserPageModel(Database *database, Logger *logger);
    ~UserPageModel() = default; // Brak wycieków - wektor przechowuje obiekty przez wartość

    bool isCurrentUserAdmin();
    std::string getCurrentUserFullName();
    
    std::vector<VehicleSummary> getRentalHistory();
    bool addVehicle(const std::string& vin, 
                    const std::string& brand, 
                    const std::string& model, 
                    const std::string& year, 
                    const std::string& color,
                    const std::string& fuelType, 
                    const std::string& technicalStatus, 
                    int mileage, 
                    int numberOfSeats, 
                    int engineCapacity, 
                    const std::string& handleBarsType, 
                    int maxCargoWeight, 
                    int numberOfAxles);
};

#endif // !USER_PAGE_MODEL_HPP