#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>

class User;

class Session {
private:
  Session();
  int userId = -1;
  std::string name = "";
  std::string surname = "";
  bool isAdmin = false;
  std::string email = "";
  bool isLoggedIn = false;

public:
  static Session &getInstance();
  void login(User *user);
  void logout();

  bool isLogged() const;
  bool getAdmin() const;
  std::string getEmail() const;
  std::string getName() const;
  std::string getSurname() const;
  int getUserId() const;
};

#endif // !SESSION_HPP
