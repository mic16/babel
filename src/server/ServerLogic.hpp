/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/

#ifndef SERVERLOGIC_HPP_
#define SERVERLOGIC_HPP_

#include <iostream>
#include <sqlite3.h> 
#include <list>
#include "../utils/Request.hpp"
#include "../dataBase/Data.hpp"
#include "../dataBase/Data.hpp"


class ServerLogic {

    static ServerLogic *singleton;

    public:
        static ServerLogic *get();
        Request executeLogic(Request request);

    private:
        Data dataBase;
        Request connect(Request request);
        Request createUser(Request request);
        ServerLogic();
        ~ServerLogic();

    protected:
};


#endif /* !SERVERLOGIC_HPP_ */
