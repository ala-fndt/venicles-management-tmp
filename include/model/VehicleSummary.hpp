#ifndef VEHICLESUMMARY_HPP
#define VEHICLESUMMARY_HPP

#include <string>

struct VehicleSummary {
  int id = 0;
  std::string brand;
  std::string model;
  std::string year;
  std::string color;
  int mileage = 0;
  int numberOfSeats = 0;
  int pricePerDay = 0;
};

#endif // !VEHICLESUMMARY_HPP
