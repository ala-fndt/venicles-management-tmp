#ifndef HOMEMODEL_HPP
#define HOMEMODEL_HPP

#include "../include/additionalScripts/Logger.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/database/Database.hpp"
#include "../include/model/VehicleSummary.hpp"
#include <string>
#include <vector>

class HomeModel {
private:
	Database *conn;
	Logger *logger;
	VehicleList vehicleList;

public:
	HomeModel(Database *conn, Logger *logger);
	int getVehicleCount();
	std::vector<VehicleSummary> getVehicles();
	std::vector<VehicleSummary> getVehiclesByQuery(const std::string &query);
	const std::vector<std::string> &getVehicleErrors() const;
};

#endif // !HOMEMODEL_HPP
