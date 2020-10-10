#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <vector>
#include <algorithm>
#include <qqml.h>
#include <iostream>
#include <thread>
#include "Clock.hpp"
#include <mutex>
#include "Communication.hpp"

class BackEnd : public QObject
{
    static BackEnd *singleton;
    Q_OBJECT;
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(QString passWord READ passWord WRITE setpassWord NOTIFY passWordChanged);
    Q_PROPERTY(QList<QString> friendlist READ friendlist);
    Q_PROPERTY(QMap<QString, QList<QString>> teamlist READ teamlist);
    Q_PROPERTY(bool microphone READ microphone WRITE setMicrophone NOTIFY microphoneChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);
    static BackEnd *get(QObject *parent = nullptr);

    QString userName();
    QString passWord();
    QList<QString> friendlist();
    QMap<QString, QList<QString>> teamlist();
    bool microphone();

    bool getQuit();

    void setUserName(const QString &userName);
    void setpassWord(const QString &passWord);
    void setMicrophone(const bool &microphone);
    Communication *getCom();
    bool isAuth();


    Q_INVOKABLE void addToFriendlist(const QString &friendName);
    Q_INVOKABLE void removeToFriendlist(const QString &friendName);
    Q_INVOKABLE void addToTeamlist(const QString &teamName);
    Q_INVOKABLE void removeToTeamlist(const QString &teamName);
    Q_INVOKABLE void addMembersToTeamlist(const QString &teamName, const QString &friendName);
    Q_INVOKABLE void removeMembersToTeamlist(const QString &teamName, const QString &friendName);
    Q_INVOKABLE bool existInTeam(const QString &teamName, const QString &friendName);
    Q_INVOKABLE bool existingTeam(const QString &Name);
    Q_INVOKABLE bool existingCredential(const QString &UserName, const QString &PassWord);
    Q_INVOKABLE bool addUserToDataBase();
    Q_INVOKABLE void fillUserInfo();
    Q_INVOKABLE void addFriendDataBase(const QString &userName);
    Q_INVOKABLE void removeFriendDataBase(const QString &userName);
    Q_INVOKABLE void addMembersTeamListDatabase(const QString &teamname, const QString &username);
    Q_INVOKABLE void removeMembersTeamListDatabase(const QString &teamname, const QString &username);
    Q_INVOKABLE bool callFriend(const QString &Name);
    Q_INVOKABLE bool callTeam(const QString &Name);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void callAccept(bool bool_accept);
    Q_INVOKABLE bool isServerOn();

    Q_INVOKABLE void display();



signals:
    void userNameChanged();
    void friendlistChanged();
    void friendlistAddChanged();
    void friendlistRemoveChanged();
    void teamlistChanged();
    void teamlistAddChanged();
    void teamlistRemoveChanged();
    void teamlistMembersAddChanged();
    void teamlistMembersRemoveChanged();
    void passWordChanged();
    void microphoneChanged();


private:
    Communication *m_com;
    std::string m_userName;
    std::string m_passWord;
    std::vector<std::string> m_friendlist;
    std::map<std::string, std::vector<std::string>> m_teamlist;
    std::vector<std::string> notiflist;
    bool m_microphone;
    bool m_quit;
    std::thread m_thread_obj;
};

#endif // BACKEND_H
