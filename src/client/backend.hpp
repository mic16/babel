#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <vector>
#include <algorithm>
#include <qqml.h>
#include <iostream>

class BackEnd : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged);
    Q_PROPERTY(QList<QString> friendlist READ friendlist);
    Q_PROPERTY(QMap<QString, QList<QString>> teamlist READ teamlist);

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString userName();
    QList<QString> friendlist();
    QMap<QString, QList<QString>> teamlist();

    void setUserName(const QString &userName);
    Q_INVOKABLE void addToFriendlist(const QString &friendName);
    Q_INVOKABLE void removeToFriendlist(const QString &friendName);
    Q_INVOKABLE void addToTeamlist(const QString &teamName);
    Q_INVOKABLE void removeToTeamlist(const QString &teamName);
    Q_INVOKABLE void addMembersToTeamlist(const QString &teamName, const QString &friendName);
    Q_INVOKABLE void removeMembersToTeamlist(const QString &teamName, const QString &friendName);
    Q_INVOKABLE bool existInTeam(const QString &teamName, const QString &friendName);
    Q_INVOKABLE bool existingTeam(const QString &Name);
    Q_INVOKABLE void display();



signals:
    void userNameChanged();
    void friendlistAddChanged();
    void friendlistRemoveChanged();
    void teamlistAddChanged();
    void teamlistRemoveChanged();
    void teamlistMembersAddChanged();
    void teamlistMembersRemoveChanged();


private:
    std::string m_userName;
    std::vector<std::string> m_friendlist;
    std::map<std::string, std::vector<std::string>> m_teamlist;
    std::vector<std::string> notiflist;
};

#endif // BACKEND_H
