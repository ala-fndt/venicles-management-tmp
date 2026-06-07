#include "../../include/classes/Motorcycle.hpp"

Motorcycle::Motorcycle(std::string brand, std::string model, std::string year,
                       std::string color, std::string licensePlate,
                       std::string vin, std::string fuelType,
                       std::string technicalStatus, int mileage,
                       int engineCapacity, std::string handleBarType)
    : Vehicle(brand, model, year, color, licensePlate, vin, fuelType,
              technicalStatus, mileage), pricePerDay(125),
      engineCapacity(engineCapacity), handleBarType(handleBarType) {}

Motorcycle::Motorcycle() {};

Motorcycle::~Motorcycle() {}

void Motorcycle::setEngineCapacity(int engineCapacity) {
  this->engineCapacity = engineCapacity;
}

void Motorcycle::setHandleBarType(std::string handleBarType) {
  this->handleBarType = handleBarType;
}

int Motorcycle::getEngineCapacity() const { return this->engineCapacity; }
std::string Motorcycle::getHandleBarType() const { return this->handleBarType; }
