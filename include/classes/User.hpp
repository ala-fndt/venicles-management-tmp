#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User {
private:
  int userId;
  std::string name;
  std::string surname;
  std::string email;
  std::string password;
  bool isAdmin;

public:
  User();

  User(std::string name, std::string surname, std::string email,
       std::string password);

  User(int userId, std::string name, std::string surname, std::string email,
       std::string password, bool isAdmin);

  virtual ~User();

  // info: settery
  void setId(int id);

  void setName(std::string name);

  void setSurname(std::string surname);

  void setEmail(std::string email);

  void setPassword(std::string password);

  void setAdminPermission(bool isAdmin);

  // info: gettery
  int getId() const;

  std::string getName() const;

  std::string getSurname() const;

  std::string getEmail() const;

  std::string getPassword() const;

  bool getAdminPermission() const;
};

#endif // !USER_HPP
