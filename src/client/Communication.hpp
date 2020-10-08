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

#include "../utils/Utils.hpp"
#include "../udpclient/Udpclient.hpp"

class Communication : public QObject {

    Q_OBJECT

public:
    Communication();
    ~Communication();

    void sendToServer(Request r);
    std::map<std::string, std::vector<std::string>> parse();

    void connectToServer();

    bool createUser(std::string name, std::string password);
    bool createTeam(std::string teamName);

    bool callUser(std::string name);
    bool getCall(std::string name);
    bool acceptCall();
    bool stopCall();

    bool addFriend(std::string name);
    bool removeFriend(std::string name);
    std::vector<std::string> getFriends(); // Yoan en a pas
    std::vector<std::string> getFriendRequests();
    bool acceptFriendRequest(std::string name);

    bool connectUser(std::string name, std::string password);
    bool disconnect();

    std::map<std::string, std::vector<std::string>> getTeams();
    bool callTeam(std::string name);
    bool getCallTeam(std::string name);
    bool addUserToTeam(std::string name);
    bool acceptTeamRequest(std::string name);

    bool changeName(std::string name);

public slots:
    void onReadyRead();

private:
    QTcpSocket  _socket;
    std::string token;
    Request lastRequestRecieve;
    UDPClient *udp;
};

#endif // COMMUNICATION_H