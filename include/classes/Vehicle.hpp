#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "User.hpp"
#include <string>

class Vehicle {
protected:
  int id;
  std::string brand;
  std::string model;
  std::string year;
  std::string color;
  std::string licensePlate;
  std::string vin;
  std::string fuelType;
  std::string technicalStatus;
  int mileage;
  int pricePerDay;

public:
  Vehicle(std::string brand, std::string model, std::string year,
          std::string color, std::string licensePlate, std::string vin,
          std::string fuelType, std::string technicalStatus, int mileage);
  Vehicle();

  virtual ~Vehicle();

  void setId(int id);
  void setBrand(std::string brand);
  void setModel(std::string model);
  void setYear(std::string year);
  void setColor(std::string color);
  void setLicensePlate(std::string licensePlate);
  void setVin(std::string vin);
  void setFuelType(std::string fuelType);
  void setTechnicalStatus(std::string technicalStatus);
  void setMileage(int mileage);

  int getId() const;
  std::string getBrand() const;
  std::string getModel() const;
  std::string getYear() const;
  std::string getColor() const;
  std::string getLicensePlate() const;
  std::string getVin() const;
  std::string getFuelType() const;
  std::string getTechnicalStatus() const;
  int getMileage() const;
  int getPricePerDay() const;
};

#endif // VEHICLE_HPP
