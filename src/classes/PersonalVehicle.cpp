#include "../../include/classes/PersonalVehicle.hpp"

PersonalVehicle::PersonalVehicle(std::string brand, std::string model,
                                 std::string year, std::string color,
                                 std::string licensePlate, std::string vin,
                                 std::string fuelType,
                                 std::string technicalStatus, int mileage,
                                 int numberOfSeats)
    : Vehicle(brand, model, year, color, licensePlate, vin, fuelType,
              technicalStatus, mileage),
      numberOfSeats(numberOfSeats) {};

PersonalVehicle::PersonalVehicle() {};

PersonalVehicle::~PersonalVehicle() {};

void PersonalVehicle::setNumberOfSeats(int numberOfSeats) {
  this->numberOfSeats = numberOfSeats;
}

int PersonalVehicle::getNumberOfSeats() const { return this->numberOfSeats; }
