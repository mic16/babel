/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Request
*/

#include "Request.hpp"


Request::Request(RequestType type, std::string content)
{
    this->content = content;
    this->type = type;
}

Request::Request(RequestType type)
{
    this->type = type;
    this->content = "";
}

Request::Request(std::string request)
{
    int posSeparation = request.find(":");
    if (posSeparation != -1) {
        this->type = static_cast<RequestType>(std::atoi(request.substr(0, posSeparation).c_str()));
        this->content = request.substr(posSeparation + 1, request.size() - posSeparation - 1);
    } else {
        this->type = static_cast<RequestType>(std::atoi(request.c_str()));
        this->content = "";
    }
}

std::string Request::getRequestToSend()
{
    int type = this->type;
    std::string request(std::to_string(type) + ":" + this->content);
    return (Utils::generateSocketMessage(request));
}

std::string Request::getRequestContent()
{
    return (this->content);
}

Request::RequestType Request::getRequestType()
{
    return (this->type);
}

Request::~Request()
{

}

