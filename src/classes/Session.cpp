#include "../include/classes/Session.hpp"
#include "../include/classes/User.hpp"

Session::Session() {};

Session &Session::getInstance() {
  static Session instance;
  return instance;
};

void Session::login(User *user) {
  this->userId = user->getId();
  this->email = user->getEmail();
  this->name = user->getName();
  this->surname = user->getSurname();
  this->isAdmin = user->getAdminPermission();
  this->isLoggedIn = true;
}

void Session::logout() {
  this->userId = -1;
  this->email = "";
  this->name = "";
  this->surname = "";
  this->isAdmin = false;
  this->isLoggedIn = false;
}

bool Session::isLogged() const { return this->isLoggedIn; }

bool Session::getAdmin() const { return this->isAdmin; }

int Session::getUserId() const { return this->userId; }

std::string Session::getName() const { return this->name; };

std::string Session::getSurname() const { return this->surname; }

std::string Session::getEmail() const { return this->email; }
