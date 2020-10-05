/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <iostream>
#include <list>
#include <sqlite3.h> 

class Data {
    public:
        Data();
        ~Data();
        std::list<std::string> select(std::string str);
        void insertRemoveUpdate(std::string str);


    private:
            sqlite3* dataBase;
            std::list<std::string> reponse;
            static int callbackSelect(void *data, int argc, char **argv, char **colName);


    protected:
};

#endif /* !DATA_HPP_ */
