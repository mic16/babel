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

}

ServerLogic::~ServerLogic()
{

}

Request ServerLogic::connect(Request request)
{
    if (this->dataBase.userExist(request.getRequestContent()))
        return (Request(Request::VALIDCONNECT));
    else
        return (Request(Request::REFUSECONNECT));
}

Request ServerLogic::createUser(Request request)
{
    if (this->dataBase.createUser(request.getRequestContent()))
        return (Request(Request::VALIDCREATEUSER));
    else {
        return (Request::Request::REFUSECREATEUSER);
    }
}

Request ServerLogic::executeLogic(Request request)
{
    Request reponse(Request::BADREQUEST);

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