/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/
/** @file */
#include "ServerLogic.hpp"
#include "TcpConnection.hpp"

ServerLogic *ServerLogic::singleton = nullptr;

ServerLogic::ServerLogic()
{

}

ServerLogic::~ServerLogic()
{

}

std::string ServerLogic::generateToken()
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return (boost::uuids::to_string(uuid));
}

ServerLogic *ServerLogic::get()
{
    if (!singleton) {
        singleton = new ServerLogic;
    }
    return (singleton);
}

Request ServerLogic::addFriend(Request request, std::string userName)
{
    std::string friends;

    if (request.getRequestContent().compare(userName) == 0 || !this->dataBase.userExist(request.getRequestContent()))
        return (Request(Request::REFUSEADDFRIEND));
    if (this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").size() > 0)
        friends.append(this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0));
    std::vector<std::string> friendsList;
    boost::split(friendsList, friends, boost::is_any_of(","));
    if (std::find(friendsList.begin(), friendsList.end(), request.getRequestContent()) != friendsList.end())
        return (Request(Request::REFUSEADDFRIEND));
    if (friends.length() != 0)
        friends.append(",");
    friends.append(request.getRequestContent());
    if (this->dataBase.insertRemoveUpdate("UPDATE users SET friends='" + friends + "' WHERE name='" + userName + "'")) {
        std::string friendsRequest;
        if (this->dataBase.select("SELECT friends_request FROM users WHERE name='" + request.getRequestContent() + "';").size() > 0)
            friendsRequest.append(this->dataBase.select("SELECT friends_request FROM users WHERE name='" + request.getRequestContent() + "';").at(0));
        if (friendsRequest.length() != 0)
            friendsRequest.append(",");
        friendsRequest.append(userName);
        this->dataBase.insertRemoveUpdate("UPDATE users SET friends_request='" + friendsRequest + "' WHERE name='" + request.getRequestContent() + "'");
        return (Request(Request::VALIDADDFRIEND));
    } else
        return (Request(Request::REFUSEADDFRIEND));
}

Request ServerLogic::removeFriend(Request request, std::string userName)
{
    if (!this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").size() > 0)
        return (Request(Request::REFUSEREMOVEFRIEND));
    std::string friends = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
    if (!friends.find(request.getRequestContent()))
        return (Request(Request::REFUSEREMOVEFRIEND));
    boost::erase_first(friends, "," + request.getRequestContent());
    boost::erase_first(friends, request.getRequestContent());
    if (this->dataBase.insertRemoveUpdate("UPDATE users set friends='" + friends + "' WHERE name='" + userName + "'"))
        return (Request(Request::VALIDREMOVEFRIEND));
    else
        return (Request(Request::REFUSEREMOVEFRIEND));
}

Request ServerLogic::getFriends(Request request, std::string userName)
{
    if (!this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").size() > 0)
        return (Request(Request::VALIDGETFRIENDS));
    std::string friends = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
    return (Request(Request::VALIDGETFRIENDS, friends));
}

// Request ServerLogic::getTeams(Request request, std::string userName)
// {
//     if (!this->dataBase.select("SELECT friends FROM teams WHERE name='" + userName + "';").size() > 0)
//         return (Request(Request::REFUSEGETTEAMS));
//     std::string teams = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
//     return (Request(Request::VALIDGETTEAMS, teams));
// }

Request ServerLogic::disconnect(Request request, std::string userName)
{
    this->usersMapTcp.erase(userName);
    this->usersMapToken.erase(request.getRequestToken());
    return (Request(Request::VALIDDISCONNECT));
}

Request ServerLogic::callUser(Request request, std::string userName)
{
    this->acceptCalls.insert(std::pair<std::string, std::string>(userName, "WAIT"));
    if (this->usersMapTcp.find(request.getRequestContent()) != this->usersMapTcp.end()) {
        TcpConnection *tcp = this->usersMapTcp.find(request.getRequestContent())->second;
        calls.insert(std::pair<std::string, std::string>(request.getRequestContent(), userName));
        return (Request(Request::VALIDCALLUSER, tcp->socket().remote_endpoint().address().to_string()));
    } else
        return (Request(Request::REFUSECALLUSER));
}

Request ServerLogic::getCall(Request request, std::string userName)
{
    if (this->calls.find(userName) != this->calls.end()) {
        Request reponse(Request::VALIDGETCALL, calls.at(userName) + "," + this->usersMapTcp.find(this->calls.at(userName))->second->socket().remote_endpoint().address().to_string());
        this->calls.erase(userName);
        return (reponse);
    }
    return (Request(Request::VALIDGETCALL));
}

Request ServerLogic::acceptCall(Request request, std::string userName)
{
    std::vector<std::string> vec;
    boost::split(vec, request.getRequestContent(), boost::is_any_of(","));
    if (this->acceptCalls.find(userName) != this->acceptCalls.end()) {
        this->acceptCalls.find(vec[0])->second = vec[1];
        return (Request(Request::VALIDACCEPTCALL));
    } else {
        return (Request(Request::REFUSEACCEPTCALL));
    }
}

Request ServerLogic::getAcceptCall(Request request, std::string userName)
{
    if (this->acceptCalls.find(userName) != this->acceptCalls.end()) {
        if (!(this->acceptCalls.find(userName)->second.compare("WAIT") == 0)) {
            Request reponse(Request::VALIDGETACCEPTCALL, this->acceptCalls.find(userName)->second);
            this->acceptCalls.erase(userName);
            return (reponse);
        } else {
            return (Request(Request::VALIDGETACCEPTCALL, "WAIT"));
        }
    }
    return (Request(Request::REFUSEGETACCEPTCALL));
}
// Request ServerLogic::changeName(Request request, std::string oldName)
// {
//     if (!this->dataBase.insertRemoveUpdate("UPDATE users SET nale='" + oldName + "' WHERE name='" + request.getRequestContent() + "'"))
//         return (Request(Request::REFUSECHANGENAME));
//     this->usersMapToken.find(request.getRequestContent())->second = request.getRequestContent();
//     TcpConnection *stock = this->usersMapTcp.find(oldName)->second;
//     this->usersMapTcp.erase(oldName);
//     this->usersMapTcp.insert(std::pair<std::string, TcpConnection *>(request.getRequestContent(), stock));
//     return (Request(Request::VALIDCHANGENAME));
// }

Request ServerLogic::connect(Request request, TcpConnection *TcpUser)
{
    if (this->dataBase.userPwdConnect(request.getRequestContent())) {
        std::string token = generateToken();
        std::vector<std::string> vec;
        boost::split(vec, request.getRequestContent(), boost::is_any_of(","));
        std::string name = vec[0];
        this->usersMapToken.insert(std::pair<std::string, std::string>(token, name));
        this->usersMapTcp.insert(std::pair<std::string, TcpConnection *>(name, TcpUser));
        return (Request(Request::VALIDCONNECT, token));
    } else
        return (Request(Request::REFUSECONNECT));
}

Request ServerLogic::createUser(Request request, TcpConnection *TcpUser)
{
    if (this->dataBase.createUser(request.getRequestContent()))
        return (Request(Request::VALIDCREATEUSER, connect(request, TcpUser).getRequestContent()));
    else
        return (Request(Request::REFUSECREATEUSER));
}

bool ServerLogic::teamExist(std::string name)
{
    std::vector<std::string> rep = this->dataBase.select("SELECT name FROM teams WHERE name='" + name + "'");
    if (rep.size() > 0)
        return (true);
    else
        return (false);
}

bool ServerLogic::userExistInTeam(std::string teamName, std::string userName)
{
    std::vector<std::string> rep = this->dataBase.select("SELECT members FROM teams WHERE name='" + teamName + "'");
    if (rep.at(0).find(userName) != std::string::npos)
        return (true);
    else
        return (false);
}

Request ServerLogic::createTeam(Request request, std::string userName)
{
    std::string teamName = request.getRequestContent();

    if (this->teamExist(teamName))
        return (Request(Request::REFUSECREATETEAM));
    if (this->dataBase.insertRemoveUpdate("INSERT INTO teams(name, members) VALUES ('" + teamName + "', '" + userName + "');"))
        return (Request(Request::VALIDCREATETEAM));
    else
        return (Request(Request::REFUSECREATETEAM));
}

Request ServerLogic::addUserToTeam(Request request)
{
    std::vector<std::string> vec;
    boost::split(vec, request.getRequestContent(), boost::is_any_of(";"));
    std::string teamName = vec[0];
    std::string userName = vec[1];

    if (this->userExistInTeam(teamName, userName) || !this->dataBase.userExist(userName))
        return (Request(Request::REFUSEADDUSERTOTEAM));
    else {
        if (!this->dataBase.select("SELECT members FROM teams WHERE name='" + teamName + "'").size() > 0)
            return (Request(Request::REFUSEADDUSERTOTEAM));
        std::string members = this->dataBase.select("SELECT members FROM teams WHERE name='" + teamName + "'").at(0);
        if (members.length() != 0)
            members.append(";");
        members.append(userName);
        if (this->dataBase.insertRemoveUpdate("UPDATE teams set members='" + members + "' WHERE name='" + teamName + "'"))
            return (Request(Request::VALIDADDUSERTOTEAM));
        else
            return (Request(Request::REFUSEADDUSERTOTEAM));
    }
}

Request ServerLogic::removeUserFromTeam(Request request)
{
    std::vector<std::string> vec;
    boost::split(vec, request.getRequestContent(), boost::is_any_of(","));
    std::string teamName = vec[0];
    std::string userName = vec[1];

    if (!this->userExistInTeam(teamName, userName) || !this->dataBase.userExist(userName))
        return (Request(Request::REFUSEREMOVEUSERFROMTEAM));
    else {
        if (!this->dataBase.select("SELECT members FROM teams WHERE name='" + teamName + "'").size() > 0)
            return (Request(Request::REFUSEREMOVEUSERFROMTEAM));
        std::string members = this->dataBase.select("SELECT members FROM teams WHERE name='" + teamName + "'").at(0);
        size_t pos = members.find(userName);
        if (pos != std::string::npos)
            members.erase(pos, userName.length());
        if (members[pos - 1] == ',')
            members.erase(pos - 1, 1);
        else if (pos == 0)
            members.erase(pos, 1);
        if (!members.size() > 0) {
            if (this->dataBase.insertRemoveUpdate("DELETE FROM teams WHERE name='" + teamName + "'"))
                return (Request(Request::VALIDREMOVEUSERFROMTEAM));
            else
                return (Request(Request::REFUSEREMOVEUSERFROMTEAM));
        }
        if (this->dataBase.insertRemoveUpdate("UPDATE teams set members='" + members + "' WHERE name='" + teamName + "'"))
            return (Request(Request::VALIDREMOVEUSERFROMTEAM));
        else
            return (Request(Request::REFUSEREMOVEUSERFROMTEAM));
    }
}

Request ServerLogic::destroyTeam(Request request)
{
    std::string teamName = request.getRequestContent();

    if (!this->teamExist(teamName))
        return (Request(Request::REFUSEDESTROYTEAM));
    else {
        if (this->dataBase.insertRemoveUpdate("DELETE FROM teams WHERE name='" + teamName + "'"))
            return (Request(Request::VALIDDESTROYTEAM));
        else
            return (Request(Request::VALIDDESTROYTEAM));

    }
}

Request ServerLogic::getFriendRequests(Request request, std::string userName)
{
    std::string friendsRequest = "";

    if (this->dataBase.select("SELECT friends_request FROM users WHERE name='" + userName + "';").size() > 0) {
        friendsRequest.append(this->dataBase.select("SELECT friends_request FROM users WHERE name='" + userName + "';").at(0));
    }
    return (Request(Request::VALIDGETFRIENDREQUESTS, friendsRequest));
}

Request ServerLogic::acceptFriendRequests(Request request, std::string userName)
{
    std::vector<std::string> content;
    boost::split(content, request.getRequestContent(), boost::is_any_of(","));
    if (this->dataBase.select("SELECT friends_request FROM users WHERE name='" + userName + "';").size() > 0) {
        std::vector<std::string> vec;
        boost::split(vec, this->dataBase.select("SELECT friends_request FROM users WHERE name='" + userName + "';").at(0), boost::is_any_of(","));
        std::string str;
        for (std::string i : vec) {
            if (i.compare(content[0]) != 0) {
                if (str.length() > 0) {
                    str.append(",");
                }
                str.append(i);
            }
        }
        this->dataBase.insertRemoveUpdate("UPDATE users SET friends_request='" + str + "' WHERE name='" + userName + "'");
        if (content[1].compare("true") == 0) {
            std::string friends = "";
            if (this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").size() > 0)
                friends.append(this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0));
            if (friends.length() != 0)
                friends.append(",");
            friends.append(content[0]);
            this->dataBase.insertRemoveUpdate("UPDATE users SET friends='" + friends + "' WHERE name='" + userName + "'");
        }
    }
    return (Request(Request::ACCEPTFRIENDREQUEST));
}

Request ServerLogic::getTeams(Request request, std::string userName)
{
    std::vector<std::string> listTeam;
    std::string res;
    if (this->dataBase.select("SELECT name FROM teams").size() > 0) {
        listTeam = this->dataBase.select("SELECT name FROM teams");
    } else {
        return (Request(Request::VALIDGETTEAMS, ""));
    }
    for (std::string team : listTeam) {
        if (this->dataBase.select("SELECT members FROM teams WHERE name='" + team + "'").size() > 0) {
            std::string t = this->dataBase.select("SELECT members FROM teams WHERE name='" + team + "'").at(0);
            if (t.find(userName) != -1) {
                if (res.length() != 0)
                    res.append(",");
                res.append(team + "(" + t + ")");
            }
        }
    }
    return (Request(Request::VALIDGETTEAMS, res));
}


Request ServerLogic::executeLogic(Request request, TcpConnection *TcpUser)
{
    std::string userName;
    if (request.getRequestType() == Request::CONNECT) {
         return (connect(request, TcpUser));
    } else if (request.getRequestType() == Request::CREATEUSER) {
        return (createUser(request, TcpUser));
    }

    if (this->usersMapToken.find(request.getRequestToken()) != this->usersMapToken.end()) {
        userName = this->usersMapToken.at(request.getRequestToken());
    } else {
        return (Request(Request::NOTCONNECTED));
    }
    switch (request.getRequestType())
    {        
        // case Request::CHANGENAME:
        //     return (changeName(request, userName));
        case Request::ADDFRIEND:
            return (addFriend(request, userName));
        case Request::DISCONNECT:
            return (disconnect(request, userName));
        case Request::REMOVEFRIEND:
            return (removeFriend(request, userName));
        case Request::GETFRIENDS:
            return (getFriends(request, userName));
        case Request::CALLUSER:
            return (callUser(request, userName));
        case Request::GETCALL:
            return (getCall(request, userName));
        case Request::ACCEPTCALL:
            return (acceptCall(request, userName));
        case Request::GETACCEPTCALL:
            return (getAcceptCall(request, userName));
        case Request::CREATETEAM:
            return (createTeam(request, userName));
        case Request::ADDUSERTOTEAM:
            return (addUserToTeam(request));
        case Request::REMOVEUSERFROMTEAM:
            return (removeUserFromTeam(request));
        case Request::GETFRIENDREQUESTS:
            return (getFriendRequests(request, userName));
        case Request::ACCEPTFRIENDREQUEST:
            return (acceptFriendRequests(request, userName));
        case Request::DESTROYTEAM:
            return (destroyTeam(request));
        case Request::GETTEAMS:
            return (getTeams(request, userName));
        default:
            return (Request(Request::BADREQUEST));
    }
}