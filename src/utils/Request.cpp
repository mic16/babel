/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Request
*/

#include "Request.hpp"

Request::Request(RequestType type, std::string content, std::string token)
{
    this->content = content;
    this->type = type;
    this->token = token;
}

Request::Request(std::string request)
{
    std::stringstream ss(request);
    std::string token;

    std::getline(ss, token, ':');
    this->type = static_cast<RequestType>(std::atoi(token.c_str()));
    std::getline(ss, token, ':');
    this->token = token;
    std::getline(ss, token, ':');
    this->content = token;
}

std::string Request::getRequestToSend()
{
    int type = this->type;
    std::string request(std::to_string(type) + ":" + this->token + ":" + this->content);
    return (Utils::generateSocketMessage(request));
}

std::string Request::getRequestContent()
{
    return (this->content);
}

std::string Request::getRequestToken()
{
    return (this->token);
}

Request::RequestType Request::getRequestType()
{
    return (this->type);
}

Request::~Request()
{

}

