#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "Vehicle.hpp"

class Truck : public Vehicle {
private:
  int maxCargoWeight;
  int numberOfAxles;
  int pricePerDay;


public:
  Truck(std::string brand, std::string model, std::string year,
        std::string color, std::string licensePlate, std::string vin,
        std::string fuelType, std::string technicalStatus, int mileage,
        int maxCargoWeight, int numberOfAxles);

  Truck();
  virtual ~Truck();

  void setMaxCargoWeight(int maxCargoWeight);
  void setNumberOfAxles(int numberOfAxles);

  int getMaxCargoWeight() const;
  int getNumberOfAxles() const;
};

#endif // !TRUCK_HPP
