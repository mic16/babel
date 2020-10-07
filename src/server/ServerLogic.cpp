/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/

#include "ServerLogic.hpp"

ServerLogic *ServerLogic::singleton = nullptr;

std::string ServerLogic::generateToken()
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return (boost::uuids::to_string(uuid));
}

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

Request ServerLogic::connect(Request request, TcpConnection *TcpUser)
{
    if (this->dataBase.userPwdConnect(request.getRequestContent())) {
        std::string token = generateToken();
        std::vector<std::string> vec;
        boost::split(vec, request.getRequestContent(), boost::is_any_of(","));
        std::string name = vec[0];
        this->usersMapToken.insert(std::pair<std::string, std::string>(token, name));
        this->usersMapTcp.insert(std::pair<std::string, TcpConnection *>(name, TcpUser));
        return (Request(Request::VALIDCONNECT, generateToken()));
    } else
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

Request ServerLogic::executeLogic(Request request, TcpConnection *TcpUser)
{
    Request reponse(Request::BADREQUEST);
    std::string userName;

    if (request.getRequestType() == Request::CONNECT) {
         return (connect(request, TcpUser));
    } else if (request.getRequestType() == Request::CREATEUSER) {
        return (createUser(request));
    }

    if (this->usersMapToken.find(request.getRequestToken()) != this->usersMapToken.end()) {
        userName = this->usersMapToken.at(request.getRequestToken());
    } else {
        return (Request(Request::NOTCONNECTED));
    }

    std::cout << request.getRequestContent() << ":" << request.getRequestType() << std::endl;

    switch (request.getRequestType())
    {        
        
    
        default:
            return (Request(Request::BADREQUEST));
    }
}