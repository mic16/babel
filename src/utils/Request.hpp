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
            //Request from clients
            CREATEUSER,         // creé l'user passé en content de la request
            CONNECT,            // connect l'user passé en content de la request

            //Request Reponse
                // Refuse
                BADREQUEST,         // request non valid
                REFUSECREATEUSER,   // refus de creer l'user
                REFUSECONNECT,      // refus de connecter l'user

                // Validate
                VALIDCONNECT,       // user conected
                VALIDCREATEUSER,    // user created

        };
        std::string getRequestToSend();
        std::string getRequestContent();
        std::string getRequestToken();
        RequestType getRequestType();

        Request(RequestType type, std::string content = "", std::string token = "");
        Request(std::string request);
        ~Request();

    private:
        std::string token;
        std::string content;
        RequestType type;
};

#endif /* !REQUEST_HPP_ */
