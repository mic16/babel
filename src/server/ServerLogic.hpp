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
#include <map> 
// #include "TcpConnection.hpp"
#include "../utils/Request.hpp"
#include "../dataBase/Data.hpp"
#include "../dataBase/Data.hpp"

class TcpConnection;

class ServerLogic {

    static ServerLogic *singleton;

    public:
        static ServerLogic *get();
        Request executeLogic(Request request, TcpConnection *TcpUser);

    private:
        int tokenId;
        Data dataBase;
        std::map<std::string, TcpConnection *> usersMapTcp; // name - Tcp
        std::map<std::string, std::string> usersMapToken;   // token - name

        std::string generateToken();
        Request connect(Request request, TcpConnection *TcpUser);
        Request createUser(Request request);
        ServerLogic();
        ~ServerLogic();

    protected:
};


#endif /* !SERVERLOGIC_HPP_ */
