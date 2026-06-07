#ifndef MOTORCYCLE_HPP
#define MOTORCYCLE_HPP

#include "Vehicle.hpp"

class Motorcycle : public Vehicle {
private:
  int engineCapacity;
  std::string handleBarType;
  int pricePerDay;

public:
  Motorcycle(std::string brand, std::string model, std::string year,
             std::string color, std::string licensePlate, std::string vin,
             std::string fuelType, std::string technicalStatus, int mileage,
             int engineCapacity, std::string handleBarType);

  Motorcycle();

  virtual ~Motorcycle();

  void setEngineCapacity(int engineCapacity);
  void setHandleBarType(std::string handleBarType);

  int getEngineCapacity() const;
  std::string getHandleBarType() const;
};

#endif // !MOTORCYCLE_HPP
