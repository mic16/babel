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

    void connectToServer();

    bool createUser(std::string name, std::string password);
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

    std::string connectUser(std::string name, std::string password);
    void disconnect();

    std::map<std::string, std::vector<std::string>> getTeams();
    void callTeam(std::string name);
    void getCallTeam(std::string name);
    void addUserToTeam(std::string name);
    void acceptTeamRequest(std::string name);

    bool changeName(std::string name);

public slots:
    void onReadyRead();

private:
    QTcpSocket  _socket;
    std::string token;

};

#endif // COMMUNICATION_H