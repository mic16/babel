/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Data
*/

#include "Data.hpp"

Data::Data()
{
    int error = 0; 
    error = sqlite3_open("src/dataBase/data.db", &dataBase); 
    if (error) { 
        std::cerr << "Error open dataBase " << sqlite3_errmsg(dataBase) << std::endl; 
    } 
    else
        std::cout << "Opened Database Successfully" << std::endl; 
    
    this->insertRemoveUpdate("CREATE TABLE users(name TEXT, pwd TEXT, friends TEXT);");
    this->insertRemoveUpdate("CREATE TABLE teams(name TEXT, members TEXT)");
}

Data::~Data()
{
    sqlite3_close(dataBase);
}

int Data::callbackSelect(void *data, int argc, char **argv, char **colName)
{
    for (int i = 0; i < argc; i++) {
        if (argv[i] == NULL) {
            break;
        }
        static_cast<std::vector<std::string>*>(data)->push_back(std::string(argv[i]));
    }
    return (0);
}

std::vector<std::string> Data::select(std::string str)
{
    int rc;
    std::vector<std::string> res;
    char *err = 0;

    rc = sqlite3_exec(this->dataBase, str.c_str(), callbackSelect, &res, &err);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    }
    return (res);
}

bool Data::insertRemoveUpdate(std::string str)
{
    int rc;
    char *err = 0;

    rc = sqlite3_exec(this->dataBase, str.c_str(), nullptr, nullptr, &err);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
        return (false);
    }
    return (true);
}

bool Data::userExist(std::string name)
{
    std::vector<std::string> rep = this->select("SELECT name FROM users WHERE name='" + name + "'");
    if (rep.size() > 0)
        return (true);
    else
        return (false);
}

bool Data::userPwdConnect(std::string content)
{
    std::vector<std::string> data;
    boost::split(data, content, boost::is_any_of(","));
    std::string name = data[0];
    std::string pwd = data[1];


    if (!this->userExist(name))
        return (false);
    std::vector<std::string> rep = this->select("SELECT name FROM users WHERE name='" + name + "' AND pwd='" + pwd + "'");
    if (rep.size() > 0)
        return (true);
    return (false);
}

bool Data::createUser(std::string content)
{
    std::vector<std::string> data;
    boost::split(data, content, boost::is_any_of(","));

    std::string name = data[0];
    std::string pwd = data[1];
    if (this->userExist(name))
        return (false);
    else
        return (this->insertRemoveUpdate("INSERT INTO users(name, pwd) VALUES ('" + name + "', '" + pwd + "');"));
}