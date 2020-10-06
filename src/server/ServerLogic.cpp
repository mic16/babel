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
    return (std::string("yolo" + this->tokenId++));
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
    if (this->dataBase.userExist(request.getRequestContent())) {
        std::string token = generateToken();
        this->usersMapToken.insert(std::pair<std::string, std::string>(token, request.getRequestContent()));
        this->usersMapTcp.insert(std::pair<std::string, TcpConnection *>(request.getRequestContent(), TcpUser));
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

    std::cout << request.getRequestType() << "/" << request.getRequestToken() << "/[" << request.getRequestContent() << "]" << std::endl;


    if (request.getRequestType() == Request::CONNECT) {
         return (connect(request, TcpUser));
    } else if (request.getRequestType() == Request::CREATEUSER) {
        return (createUser(request));
    }

    if (this->usersMapToken.find(request.getRequestToken()) != this->usersMapToken.end())
        userName = this->usersMapToken.at(request.getRequestToken());

    switch (request.getRequestType())
    {        
        
    
        default:
            return (Request(Request::BADREQUEST));
    }
}