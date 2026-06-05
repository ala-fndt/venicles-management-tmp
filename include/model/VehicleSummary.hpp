#ifndef VEHICLESUMMARY_HPP
#define VEHICLESUMMARY_HPP

#include <string>

struct VehicleSummary {
  int id = -1;
  std::string brand;
  std::string model;
  std::string year;
  std::string color;
};

#endif // !VEHICLESUMMARY_HPP