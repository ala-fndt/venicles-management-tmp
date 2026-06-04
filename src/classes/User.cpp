#include "../../include/classes/User.hpp"

User::User(int userId, std::string name, std::string surname, std::string email,
           std::string password, bool isAdmin)
    : userId(userId), name(name), surname(surname), email(email),
      password(password), isAdmin(isAdmin) {}

User::User(std::string name, std::string surname, std::string email,
           std::string password)
    : name(name), surname(surname), email(email), password(password) {}

User::User() {};

User::~User() {}

void User::setId(int userId) { this->userId = userId; }

void User::setName(std::string name) { this->name = name; }

void User::setSurname(std::string surname) { this->surname = surname; }

void User::setEmail(std::string email) { this->email = email; }

void User::setPassword(std::string password) { this->password = password; }

void User::setAdminPermission(bool isAdmin) { this->isAdmin = isAdmin; }

std::string User::getName() const { return name; }

std::string User::getSurname() const { return surname; }

std::string User::getEmail() const { return email; }

std::string User::getPassword() const { return password; }

int User::getId() const { return userId; }

bool User::getAdminPermission() const { return isAdmin; }
