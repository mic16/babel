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
    Communication();
    ~Communication();

    void sendToServer(Request r);
    std::map<std::string, std::vector<std::string>> parse();

    void connectToServer();

    bool isServerOn();

    bool createUser(std::string name, std::string password);
    bool createTeam(std::string teamName);

    bool callUser(std::string name);
    std::string getCall();
    bool acceptCall(bool response, std::string calledUser);
    bool stopCall();
    int getAcceptCall();
    bool hangUpFriend();

    bool addFriend(std::string name);
    bool removeFriend(std::string name);
    std::vector<std::string> getFriends(); // Yoan en a pas
    std::vector<std::string> getFriendRequests();
    bool acceptFriendRequest(std::string name, bool value);

    bool connectUser(std::string name, std::string password);
    bool disconnect();

    std::map<std::string, std::vector<std::string>> getTeams();
    bool callTeam(std::string name);
    bool getCallTeam(std::string name);
    bool addUserToTeam(std::string userName, std::string teamName);
    bool removeUserFromTeam(std::string userName, std::string teamName);
    bool acceptTeamRequest(std::string name);
    bool destroyTeam(std::string name);
    bool changeName(std::string name);
    std::string getUserIP();

public slots:
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