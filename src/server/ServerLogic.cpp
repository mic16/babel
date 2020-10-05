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
    std::list<std::string> rep =  this->dataBase.select("SELECT * FROM users WHERE name='" + request.getRequestContent() + "'");
    if (rep.size() > 0)
        return (Request(Request::CONNECT));

    return (Request(Request::REFUSECONNECT));
}

Request ServerLogic::createUser(Request request)
{
    // TODO code ici (le return c'est le cas en cas d'echec)
    return Request(Request::REFUSECREATE);
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