/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Request
*/
/** @file */

#include "Request.hpp"

Request::Request()
{

}

Request::Request(RequestType type, std::string content, std::string token)
{
    this->content = content;
    this->type = type;
    this->token = token;
}

Request::Request(std::string request)
{
    std::vector<std::string> data;
    boost::split(data, request, boost::is_any_of(":"));

    this->type = static_cast<RequestType>(std::atoi(data[0].c_str()));
    this->token = data[1];
    this->content = data[2];
}

std::string Request::getRequestToSend()
{
    int type = this->type;
    std::string request(std::to_string(type) + ":" + this->token + ":" + this->content + ":");
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

