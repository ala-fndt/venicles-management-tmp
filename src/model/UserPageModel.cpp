#include "../../include/model/UserPageModel.hpp"
#include "../../include/classes/Session.hpp"
#include <sqlite3.h>

UserPageModel::UserPageModel(Database *db, Logger *logger)
    : database(db), logger(logger) {}

bool UserPageModel::isCurrentUserAdmin() {
    return Session::getInstance().getAdmin();
}

std::string UserPageModel::getCurrentUserFullName() {
    if (!Session::getInstance().isLogged()) return "Gość";
    return Session::getInstance().getName() + " " + Session::getInstance().getSurname();
}

bool UserPageModel::addVehicle(const std::string& vin, const std::string& brand, const std::string& model, 
                               const std::string& year, const std::string& color, const std::string& fuelType, 
                               const std::string& status, int mileage, int seats, int engine, 
                               const std::string& handle, int cargo, int axles) {
    if (!database) return false;
    
    auto sanitize = [](std::string str) {
        size_t pos = 0;
        while ((pos = str.find("'", pos)) != std::string::npos) {
            str.replace(pos, 1, "''");
            pos += 2;
        }
        return str;
    };

    std::string sql = "INSERT INTO vehicle (vin, brand, model, year, color, fuelType, technicalStatus, mileage, "
                      "numberOfSeats, engineCapacity, handleBarsType, maxCargoWeight, numberOfAxles) VALUES ("
                      "'" + sanitize(vin) + "', "
                      "'" + sanitize(brand) + "', "
                      "'" + sanitize(model) + "', "
                      "'" + sanitize(year) + "', "
                      "'" + sanitize(color) + "', "
                      "'" + sanitize(fuelType) + "', "
                      "'" + sanitize(status) + "', "
                      + std::to_string(mileage) + ", "
                      + (seats > 0 ? std::to_string(seats) : "NULL") + ", "
                      + (engine > 0 ? std::to_string(engine) : "NULL") + ", "
                      "'" + sanitize(handle) + "', "
                      + (cargo > 0 ? std::to_string(cargo) : "NULL") + ", "
                      + (axles > 0 ? std::to_string(axles) : "NULL") + ");";

    database->executeQuery(sql);
    return true; 
}

std::vector<VehicleSummary> UserPageModel::getRentalHistory() {
    if (!database || !Session::getInstance().isLogged()) return {};

    int userId = Session::getInstance().getUserId();

    // Zapytanie łączące tabelę historii z danymi pojazdów
    std::string sql = "SELECT v.brand, v.model, v.year, v.color "
                      "FROM vehicle v "
                      "JOIN rentalHistory rh ON v.id = rh.idVehicle "
                      "WHERE rh.idUser = " + std::to_string(userId) + ";";

    // Mapowanie wyników z bazy danych na strukturę VehicleSummary
    auto mapper = [](sqlite3_stmt* stmt) -> VehicleSummary {
        VehicleSummary vs;
        const unsigned char* brand = sqlite3_column_text(stmt, 0);
        const unsigned char* model = sqlite3_column_text(stmt, 1);
        const unsigned char* year = sqlite3_column_text(stmt, 2);
        const unsigned char* color = sqlite3_column_text(stmt, 3);

        vs.brand = brand ? reinterpret_cast<const char*>(brand) : "";
        vs.model = model ? reinterpret_cast<const char*>(model) : "";
        vs.year = year ? reinterpret_cast<const char*>(year) : "";
        vs.color = color ? reinterpret_cast<const char*>(color) : "";
        return vs;
    };

    return database->fetch<VehicleSummary>(sql, mapper);
}