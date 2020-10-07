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
#include "../dataBase/Data.hpp"

class TcpConnection;

class ServerLogic {

    static ServerLogic *singleton;

    public:
        static ServerLogic *get();
        Request executeLogic(Request request, TcpConnection *TcpUser);

    private:
        Data dataBase;
        std::map<std::string, TcpConnection *> usersMapTcp; // name - Tcp
        std::map<std::string, std::string> usersMapToken;   // token - name

        std::string generateToken();
        Request connect(Request request, TcpConnection *TcpUser);
        Request createUser(Request request);



        bool createTeam(std::map<std::string, std::vector<std::string>> team);

        void callUser(std::string name);
        void getCall(std::string name);
        void acceptCall();
        void stopCall();

        void addFriend(std::string name);
        void removeFriend(std::string name);
        std::vector<std::string> getFriends(); // Yoan en a pas
        std::vector<std::string> getFriendRequests();
        void acceptFriendRequest(std::string name);
        void disconnect();
        std::map<std::string, std::vector<std::string>> getTeams();
        void callTeam(std::string name);
        void getCallTeam(std::string name);
        void addUserToTeam(std::string name);
        void acceptTeamRequest(std::string name);

        Request changeName(Request request, std::string oldName);


        ServerLogic();
        ~ServerLogic();

    protected:
};


#endif /* !SERVERLOGIC_HPP_ */
