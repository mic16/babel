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

        /**
        * std::string generateToken();
        *
        * Generates a token that identifies users when logged in
        */
        std::string generateToken();
        /**
        * Request connect(Request request, TcpConnection *TcpUser);
        *
        * Connects user to server if username and pwd are good
        */
        Request connect(Request request, TcpConnection *TcpUser);
        /**
        * Request disconnect(Request request, std::string userName);
        *
        * Disconnects user from server
        */
        Request disconnect(Request request, std::string userName);
        /**
        * Request createUser(Request request, TcpConnection *TcpUser);
        *
        * Creates user in database
        */
        Request createUser(Request request, TcpConnection *TcpUser);

        /**
        * Request addFriend(Request request, std::string userName);
        *
        * Adds user to friendlist in database
        */
        Request addFriend(Request request, std::string userName);
        /**
        * Request removeFriend(Request request, std::string userName);
        *
        * Removes user from friendlist in database
        */
        Request removeFriend(Request request, std::string userName);
        /**
        * Request getFriends(Request request, std::string userName);
        *
        * Sends friendlist to user from database
        */
        Request getFriends(Request request, std::string userName); // Yoan en a pas
        /**
        * Request getFriendRequests(Request request, std::string userName);
        *
        * Sends friend request list to user from database
        */
        Request getFriendRequests(Request request, std::string userName);
        /**
        * Request acceptFriendRequests(Request request, std::string userName);
        *
        * Adds both users to eachother's friendlist
        */
        Request acceptFriendRequests(Request request, std::string userName);

        /**
        * Request callUser(Request request, std::string userName);
        *
        * Calls specified user by sending his IP to the original user
        */
        Request callUser(Request request, std::string userName);
        /**
        * Request getCall(Request request, std::string userName);
        *
        * Sends a notification if a user is getting called
        */
        Request getCall(Request request, std::string userName);
        /**
        * Request acceptCall(Request request, std::string userName);
        *
        * Gets info from the user that received the call if he accepted or refused the call
        */
        Request acceptCall(Request request, std::string userName);
        /**
        * Request getAcceptCall(Request request, std::string userName);
        *
        * Sends info to the user that called if the other user accepted or refused the call
        */
        Request getAcceptCall(Request request, std::string userName);
        /**
        * void stopCall();
        *
        * Sends inof that the other user stopped the call
        */
        void stopCall();

        /**
        * Request createTeam(Request request, std::string userName);
        *
        * Creates team in the database
        */
        Request createTeam(Request request, std::string userName);
        /**
        * Request addUserToTeam(Request request);
        *
        * Adds user to team in database
        */
        Request addUserToTeam(Request request);
        /**
        * Request removeUserFromTeam(Request request);
        *
        * Removes user from team
        */
        Request removeUserFromTeam(Request request);
        /**
        * Request destroyTeam(Request request);
        *
        * Destroys team in database
        */
        Request destroyTeam(Request request);
        /**
        * Request getTeams(Request request, std::string userName);
        *
        * Sends teams to user
        */
        Request getTeams(Request request, std::string userName);

        /**
        * bool teamExist(std::string name);
        *
        * Checks if team exists
        */
        bool teamExist(std::string name);
        /**
        * bool userExistInTeam(std::string teamName, std::string userName);
        *
        * Checks if user exists in team
        */
        bool userExistInTeam(std::string teamName, std::string userName);
        
        // Request changeName(Request request, std::string oldName);




        /**
        * void acceptTeamRequest(std::string name);
        *
        * Accepts team request
        */
        void acceptTeamRequest(std::string name);



        /**
        * void acceptFriendRequest(std::string name);
        *
        * Sends accept friend request
        */
        void acceptFriendRequest(std::string name);



        /**
        * ServerLogic();
        *
        * ServerLogic constructor
        */
        ServerLogic();
        /**
        * ~ServerLogic();
        *
        * ServerLogic deconstructor
        */
        ~ServerLogic();

    protected:
};


#endif /* !SERVERLOGIC_HPP_ */
