#include "../../include/model/UserPageModel.hpp"

UserPageModel::~UserPageModel() = default;

UserPageModel::UserPageModel(Database *db, Logger *logger)
    : database(db), logger(logger), router(nullptr) {}

bool UserPageModel::addVehicle(const std::string& vin, const std::string& brand, const std::string& model, 
                                const std::string& year, const std::string& color, const std::string& fuelType, 
                                const std::string& status, int mileage, int seats, int engine, 
                                const std::string& handle, int cargo, int axles) {
  
    
    std::string sql = "INSERT INTO vehicle (vin, brand, model, year, color, fuelType, technicalStatus, mileage, "
                      "numberOfSeats, engineCapacity, handleBarsType, maxCargoWeight, numberOfAxles) VALUES ("
                      "'" + vin + "', "
                      "'" + brand + "', "
                      "'" + model + "', "
                      "'" + year + "', "
                      "'" + color + "', "
                      "'" + fuelType + "', "
                      "'" + status + "', "
                      + std::to_string(mileage) + ", "
                      + (seats > 0 ? std::to_string(seats) : "NULL") + ", "
                      + (engine > 0 ? std::to_string(engine) : "NULL") + ", "
                      "'" + handle + "', "
                      + (cargo > 0 ? std::to_string(cargo) : "NULL") + ", "
                      + (axles > 0 ? std::to_string(axles) : "NULL") + ");";

    if (database) {
        database->executeQuery(sql);
        // W tej architekturze błędy są logowane przez klasę Database.
        return true; 
    }
    
    return false;
}

std::vector<VehicleSummary> UserPageModel::getRentalHistory() {
    // Metoda wymagana do odświeżania widoku historii wynajmu.
    // Tutaj możesz dodać zapytanie SELECT do tabeli rentalHistory w przyszłości.
    return {};
}