/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/

#include "ServerLogic.hpp"

ServerLogic *ServerLogic::singleton = nullptr;

ServerLogic *ServerLogic::get()
{
    if (!singleton) {
        singleton = new ServerLogic;
    }
    return (singleton);
}

ServerLogic::ServerLogic()
{
    int error = 0; 
    error = sqlite3_open("src/dataBase/data.db", &dataBase); 
    if (error) { 
        std::cerr << "Error open dataBase " << sqlite3_errmsg(dataBase) << std::endl; 
    } 
    else
        std::cout << "Opened Database Successfully" << std::endl; 
}

ServerLogic::~ServerLogic()
{
    sqlite3_close(dataBase); 
}

Request ServerLogic::connect(Request request)
{
    std::cout << "connect function" << std::endl;
    return Request(Request::BADREQUEST);
}

Request ServerLogic::createUser(Request request)
{
    return Request(Request::BADREQUEST);
}

Request ServerLogic::executeLogic(Request request)
{
    Request reponse(Request::BADREQUEST);

    std::cout << "logic" << request.getRequestType() << std::endl;
    switch (request.getRequestType())
    {
        case Request::CONNECT :
            reponse = connect(request);
            break;
        
        case Request::CREATEUSER :
            reponse = createUser(request);
            break;
    
    default:
        break;
    }
    return (reponse);
}