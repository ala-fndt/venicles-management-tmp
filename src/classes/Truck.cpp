#include "../../include/classes/Truck.hpp"

Truck::Truck(std::string brand, std::string model, std::string year,
             std::string color, std::string licensePlate, std::string vin,
             std::string fuelType, std::string technicalStatus, int mileage,
             int maxCargoWeight, int numberOfAxles)
    : Vehicle(brand, model, year, color, licensePlate, vin, fuelType,
              technicalStatus, mileage), pricePerDay(450),
      maxCargoWeight(maxCargoWeight), numberOfAxles(numberOfAxles) {}

Truck::Truck() {};

Truck::~Truck() {};

void Truck::setMaxCargoWeight(int maxCargoWeight) {
  this->maxCargoWeight = maxCargoWeight;
}

void Truck::setNumberOfAxles(int numberOfAxles) {
  this->numberOfAxles = numberOfAxles;
}

int Truck::getMaxCargoWeight() const { return this->maxCargoWeight; }
int Truck::getNumberOfAxles() const { return this->numberOfAxles; }
