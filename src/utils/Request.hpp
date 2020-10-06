/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <iostream>
#include "Utils.hpp"

class Request {
    public:
        enum RequestType {
            CREATEUSER,         // creé l'user passé en content de la request
            CONNECT,            // connect l'user passé en content de la request
            BADREQUEST,         // request non valid
            REFUSECREATE,       // refus de creer l'user
            REFUSECONNECT,      // refus de connecter l'user
        };
        std::string getRequestToSend();
        std::string getRequestContent();
        RequestType getRequestType();
        Request(RequestType type, std::string content);
        Request(RequestType type);
        Request(std::string request);
        ~Request();

    private:
        std::string content;
        RequestType type;
};

#endif /* !REQUEST_HPP_ */
