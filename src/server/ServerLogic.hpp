/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/

#ifndef SERVERLOGIC_HPP_
#define SERVERLOGIC_HPP_

#include <iostream>
#include <sqlite3.h> 
#include <vector>
#include <map> 
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp> 
#include "../utils/Utils.hpp"
#include "../utils/Request.hpp"
#include "../dataBase/Data.hpp"

class TcpConnection;

class ServerLogic {

    static ServerLogic *singleton;

    public:
        static ServerLogic *get();
        Request executeLogic(Request request, TcpConnection *TcpUser);

    private:
        Data dataBase;
        std::map<std::string, std::string> calls;
        std::map<std::string, std::string> acceptCalls;
        std::map<std::string, TcpConnection *> usersMapTcp; // name - Tcp
        std::map<std::string, std::string> usersMapToken;   // token - name

        std::string generateToken();
        Request connect(Request request, TcpConnection *TcpUser);
        Request disconnect(Request request, std::string userName);
        Request createUser(Request request, TcpConnection *TcpUser);

        Request addFriend(Request request, std::string userName);
        Request removeFriend(Request request, std::string userName);
        Request getFriends(Request request, std::string userName); // Yoan en a pas
        Request getFriendRequests(Request request, std::string userName);
        Request acceptFriendRequests(Request request, std::string userName);

        Request callUser(Request request, std::string userName);
        Request getCall(Request request, std::string userName);
        Request acceptCall(Request request, std::string userName);
        Request getAcceptCall(Request request, std::string userName);
        void stopCall();

        Request createTeam(Request request, std::string userName);
        Request addUserToTeam(Request request);
        Request addUserToTeam(std::string name);
        Request removeUserFromTeam(Request request);
        Request destroyTeam(Request request);
        Request getTeams(Request request, std::string userName);

        bool teamExist(std::string name);
        bool userExistInTeam(std::string teamName, std::string userName);
        
        // Request changeName(Request request, std::string oldName);




        void acceptTeamRequest(std::string name);



        void getCallTeam(std::string name);



        void acceptFriendRequest(std::string name);
        void callTeam(std::string name);



        ServerLogic();
        ~ServerLogic();

    protected:
};


#endif /* !SERVERLOGIC_HPP_ */
