#ifndef PERSONALVEHICLE_HPP
#define PERSONALVEHICLE_HPP

#include "Vehicle.hpp"
#include <string>

class PersonalVehicle : public Vehicle {
private:
  int numberOfSeats;

public:
  PersonalVehicle(std::string brand, std::string model, std::string year,
                  std::string color, std::string licensePlate, std::string vin,
                  std::string fuelType, std::string technicalStatus,
                  int mileage, int numberOfSeats);

  PersonalVehicle();

  virtual ~PersonalVehicle();

  void setNumberOfSeats(int numberOfSeats);
  int getNumberOfSeats() const;
};

#endif // !PERSONALVEHICLE_HPP
