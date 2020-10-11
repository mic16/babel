/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Request
*/
/** @file */

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <iostream>
#include "Utils.hpp"

class Request {
    public:
        enum RequestType {
            //Request from clients
            CREATEUSER,         // creé l'user passé en content de la request
            CREATETEAM,         // crée la team passé en content de la request
            
            CONNECT,            // connect l'user passé en content de la request
            DISCONNECT,
            
            CALLUSER,           // call l'user passé en content de la request
            ACCEPTCALL,         // accept le call du user passé en content de la request
            STOPCALL,           // arrêter le call
            GETACCEPTCALL,

            ADDFRIEND,          // ajouter un user passé en content de la request à sa liste d'amis
            REMOVEFRIEND,       // enlever un user passé en content de la request de sa liste d'amis
            GETFRIENDS,         // get les amis du user
            GETFRIENDREQUESTS,  // get les demandes d'amis du user
            ACCEPTFRIENDREQUEST,// accept la demande d'ami

            GETTEAMS,           // get les teams du user
            CALLTEAM,           // call tous les user de la team passé en content de la request
            ADDUSERTOTEAM,      // ajouter un user passé en content de la request à la team passé en content de la request
            REMOVEUSERFROMTEAM, // enlever un user passé en content de la request à la team passé en content de la request
            ACCEPTTEAMREQUEST,  // accept la demande à rejoindre une team
            DESTROYTEAM,

            CHANGENAME,         // changer le nom d'un user (pas sûr encore)

            //Request from server
            GETCALL,            // get le call du user passé en content de la request
            GETCALLTEAM,        // get le call de la team passé en content de la request

            //Request Reponse
                // Refuse
                NOTCONNECTED,               // If the user is not connected
                BADREQUEST,                 // request non valid

                REFUSECONNECT,              // refus de connecter l'user
                REFUSEDISCONNECT,           //

                REFUSECREATEUSER,           // refus de creer l'user
                REFUSECREATETEAM,           // refus de créer la team

                REFUSECALLUSER,             // refus de call l'user
                REFUSEGETCALL,              // refus de get les calls
                REFUSEACCEPTCALL,           // refus d'accept le call
                REFUSESTOPCALL,             // refus d'arrêter le call
                REFUSEGETACCEPTCALL,

                REFUSEADDFRIEND,            // refus de rajouter un ami
                REFUSEREMOVEFRIEND,         // refus d'enlever un ami
                REFUSEGETFRIENDS,           // refus de get ses amis
                REFUSEGETFRIENDREQUESTS,    // refus de get les demandes d'amis
                REFUSEACCEPTFRIENDREQUEST,  // refus d'accept une demande d'ami
                REFUSEDESTROYTEAM,

                REFUSEGETTEAMS,             // refus de get ses teams
                REFUSECALLTEAM,             // refus de call une team
                REFUSEGETCALLTEAM,          // refus de get le call d'une team
                REFUSEADDUSERTOTEAM,        // refus de add un user à une team
                REFUSEREMOVEUSERFROMTEAM,   // refus de remove un user d'une team
                REFUSEACCEPTTEAMREQUEST,    // refus d'accept une demande de team

                REFUSECHANGENAME,           // refus de géchan le nom
                

                // Validate
                VALIDCONNECT,               // user connected
                VALIDDISCONNECT,            // user disconnected

                VALIDCREATEUSER,            // user created
                VALIDCREATETEAM,

                VALIDCALLUSER,              // user called
                VALIDGETCALL,               // user a reçu le call
                VALIDACCEPTCALL,            // user a accepté le call
                VALIDSTOPCALL,              // user a arrêté le call
                VALIDGETACCEPTCALL,

                VALIDADDFRIEND,             // user a rajouté un ami
                VALIDREMOVEFRIEND,          // user a enlevé un ami
                VALIDGETFRIENDS,            // user a reçu ses amis
                VALIDGETFRIENDREQUESTS,     // user a reçu sa liste de demande d'amis
                VALIDACCEPTFRIENDREQUEST,   // user a accepté la demande d'ami

                VALIDGETTEAMS,              // user a reçu ses teams
                VALIDCALLTEAM,              // user a appelé une team
                VALIDGETCALLTEAM,           // user a reçu un call d'une team
                VALIDADDUSERTOTEAM,         // user a rajouté un user à une team
                VALIDREMOVEUSERFROMTEAM,    // user a enlevé un user à une team
                VALIDACCEPTTEAMREQUEST,     // user a accepté la demande de team
                VALIDDESTROYTEAM,

                VALIDCHANGENAME,            // user a changé de nom

        };

        std::string getRequestToSend();
        std::string getRequestContent();
        std::string getRequestToken();
        RequestType getRequestType();

        Request();
        Request(RequestType type, std::string content = "", std::string token = "");
        Request(std::string request);
        ~Request();

    private:
        std::string token;
        std::string content;
        RequestType type;
};

#endif /* !REQUEST_HPP_ */
