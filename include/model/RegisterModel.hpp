#ifndef REGISTERMODEL_HPP
#define REGISTERMODEL_HPP

#include "../database/Database.hpp"
#include "../additionalScripts/Logger.hpp"
#include <string>
#include <vector>

class RegisterModel {
private:
    Database* conn;
    Logger* logger;
    std::vector<std::string> errors;

public:
    RegisterModel(Database* conn, Logger* logger);
    ~RegisterModel();

    bool checkUserExists(const std::string& email);
    bool registerUser(const std::string& name, const std::string& surname, const std::string& email, const std::string& password);
    std::vector<std::string> getErrors();
};

#endif // !REGISTERMODEL_HPP
