/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/
/** @file */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <vector>
#include <map>

#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QtCore>
#include <QtNetwork>
#include <QApplication>
#include <QMainWindow>

#include "../utils/Request.hpp"
#include "../utils/Utils.hpp"

class Communication : public QObject{

    Q_OBJECT

public:
    /**
    * Communication();
    *
    * Communication constructor
    */
    Communication();
    /**
    * ~Communication();
    *
    * Communication deconstructor
    */
    ~Communication();

    /**
    * void sendToServer(Request r);
    *
    * Sends request to server
    */
    void sendToServer(Request r);
    /**
    * std::map<std::string, std::vector<std::string>> parse()();
    *
    * Parses team string received from server
    */
    std::map<std::string, std::vector<std::string>> parse();

    /**
    * void connectToServer();
    *
    * Connects to server
    */
    void connectToServer();

    /**
    * bool isServerOn();
    *
    * Checks if server is on
    */
    bool isServerOn();

    /**
    * bool createUser(std::string name, std::string password);
    *
    * Creates user in database
    */
    bool createUser(std::string name, std::string password);
    /**
    * bool createTeam(std::string teamName);
    *
    * Create team in database
    */
    bool createTeam(std::string teamName);

    /**
    * bool callUser(std::string name);
    *
    * Calls the specified user
    */
    bool callUser(std::string name);
    /**
    * std::string getCall();
    *
    * Checks if user is getting called
    */
    std::string getCall();
    /**
    * bool acceptCall(bool response, std::string calledUser);
    *
    * Accepts call
    */
    bool acceptCall(bool response, std::string calledUser);
    /**
    * bool stopCall();
    *
    * Stops call
    */
    bool stopCall();
    /**
    * int getAcceptCall();
    *
    * Checks if other user accepted or refused to call
    */
    int getAcceptCall();
    /**
    * bool hangUpFriend();
    *
    * Stops call
    */
    bool hangUpFriend();

    /**
    * bool addFriend(std::string name);
    *
    * Adds friend to friendlist in database
    */
    bool addFriend(std::string name);
    /**
    * bool removeFriend(std::string name);
    *
    * Removes friend from friendlist in database
    */
    bool removeFriend(std::string name);
    /**
    * std::vector<std::string> getFriends();
    *
    * Get friend list from server
    */
    std::vector<std::string> getFriends(); // Yoan en a pas
    /**
    * std::vector<std::string> getFriendRequests();
    *
    * Get friend request list from server
    */
    std::vector<std::string> getFriendRequests();
    /**
    * bool acceptFriendRequest(std::string name, bool value);
    *
    * Accepts friend request
    */
    bool acceptFriendRequest(std::string name, bool value);

    /**
    * bool connectUser(std::string name, std::string password);
    *
    * Connects user
    */
    bool connectUser(std::string name, std::string password);
    /**
    * bool disconnect();
    *
    * Disconnects user
    */
    bool disconnect();

    /**
    * std::map<std::string, std::vector<std::string>> getTeams();
    *
    * Get team list from server
    */
    std::map<std::string, std::vector<std::string>> getTeams();
    /**
    * bool addUserToTeam(std::string userName, std::string teamName);
    *
    * Adds user to team
    */
    bool addUserToTeam(std::string userName, std::string teamName);
    /**
    * bool removeUserFromTeam(std::string userName, std::string teamName);
    *
    * Removes user from team
    */
    bool removeUserFromTeam(std::string userName, std::string teamName);
    /**
    * bool acceptTeamRequest(std::string name);
    * 
    * Accepts team request
    */
    bool acceptTeamRequest(std::string name);
    /**
    * bool destroyTeam(std::string name);
    *
    * Destroys team
    */
    bool destroyTeam(std::string name);
    /**
    * std::string getUserIP();
    *
    * Get user's IP
    */
    std::string getUserIP();

public slots:
    /**
    * void onReadyRead();
    *
    * Reads anything sent from server
    */
    void onReadyRead();

private:
    QTcpSocket  _socket;
    std::string token;
    Request lastRequestRecieve;
    bool call;
    bool connected;
    std::string userIP;
};

#endif // COMMUNICATION_H