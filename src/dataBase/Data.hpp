/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <iostream>
#include <vector>
#include <sqlite3.h> 
#include "../utils/Utils.hpp"

class Data {
    public:
        Data();
        ~Data();
        bool userIsConnected(std::string name);
        bool userExist(std::string name);
        bool createUser(std::string content);
        bool userPwdConnect(std::string content);
        std::vector<std::string> select(std::string str);
        void insertRemoveUpdate(std::string str);


    private:
            sqlite3* dataBase;
            std::vector<std::string> reponse;
            static int callbackSelect(void *data, int argc, char **argv, char **colName);


    protected:
};

#endif /* !DATA_HPP_ */
