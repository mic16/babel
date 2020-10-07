/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** ServerLogic
*/

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
    std::string friends = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
    std::vector<std::string> friendsList;
    boost::split(friendsList, friends, boost::is_any_of(","));
    if (std::find(friendsList.begin(), friendsList.end(), request.getRequestContent()) != friendsList.end())
        return (Request(Request::REFUSEADDFRIEND));
    if (friends.length() != 0)
        friends.append(",");
    friends.append(request.getRequestContent());
    if (this->dataBase.insertRemoveUpdate("UPDATE users SET friends='" + friends + "' WHERE name='" + userName + "'")) {
      
        return (Request(Request::VALIDADDFRIEND));
    } else
        return (Request(Request::REFUSEADDFRIEND));
}

Request ServerLogic::removeFriend(Request request, std::string userName)
{
    std::string friends = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
    boost::erase_first(friends, "," + request.getRequestContent());
    boost::erase_first(friends, request.getRequestContent());
    if (this->dataBase.insertRemoveUpdate("UPDATE users set friends='" + friends + "' WHERE name='" + userName + "'"))
        return (Request(Request::VALIDREMOVEFRIEND));
    else
        return (Request(Request::REFUSEREMOVEFRIEND));
}

 Request ServerLogic::getFriends(Request request, std::string userName)
 {
    std::string friends = this->dataBase.select("SELECT friends FROM users WHERE name='" + userName + "';").at(0);
    return (Request(Request::VALIDGETFRIENDS, friends));
 }

Request ServerLogic::disconnect(Request request, std::string userName)
{
    this->usersMapTcp.erase(userName);
    this->usersMapToken.erase(request.getRequestToken());
    return (Request(Request::VALIDDISCONNECT));
}

Request ServerLogic::callUser(Request request)
{
    if (this->usersMapTcp.find(request.getRequestContent()) != this->usersMapTcp.end()) {
        TcpConnection *tcp = this->usersMapTcp.find(request.getRequestContent())->second;
        return (Request(Request::VALIDCALLUSER), tcp->socket().remote_endpoint().address().to_string());
    } else
        return (Request(Request::REFUSECALLUSER));
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

Request ServerLogic::createUser(Request request)
{
    if (this->dataBase.createUser(request.getRequestContent()))
        return (Request(Request::VALIDCREATEUSER));
    else {
        return (Request::Request::REFUSECREATEUSER);
    }
}

Request ServerLogic::executeLogic(Request request, TcpConnection *TcpUser)
{
    std::string userName;
    if (request.getRequestType() == Request::CONNECT) {
         return (connect(request, TcpUser));
    } else if (request.getRequestType() == Request::CREATEUSER) {
        return (createUser(request));
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
        
        default:
            return (Request(Request::BADREQUEST));
    }
}