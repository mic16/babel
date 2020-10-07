#include "Communication.hpp"

Communication::Communication()
{
    connectToServer();
}

Communication::~Communication()
{

}

void Communication::connectToServer()
{
    _socket.connectToHost(QHostAddress("127.0.0.1"), 7171);
    _socket.waitForConnected();
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Communication::sendToServer(Request r)
{
    QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    _socket.write(str, r.getRequestToSend().size());
    _socket.waitForReadyRead();
}

void Communication::onReadyRead()
{
    QByteArray str = _socket.read(4);
    QByteArray rep = _socket.read(Utils::convertBytesArrayToSizeT(reinterpret_cast<unsigned char *>(str.data())));

    lastRequestRecieve = Request(rep.data());
    std::cout << lastRequestRecieve.getRequestType() << ":" << lastRequestRecieve.getRequestContent()  << ":" << lastRequestRecieve.getRequestToken() << std::endl;
}

bool Communication::createUser(std::string name, std::string password)
{
    Request r(Request::CREATEUSER, name + "," + password);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATEUSER)
        return (true);
    else
        return (false);
}

bool Communication::createTeam(std::string teamName)
{
    Request r(Request::CREATETEAM, teamName, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATETEAM)
        return (true);
    else
        return (false);
}

void Communication::callUser(std::string name)
{
    Request r(Request::CALLUSER, name, token);
    sendToServer(r);
}

void Communication::getCall(std::string name)
{

}

void Communication::acceptCall()
{
    Request r(Request::ACCEPTCALL, "",token);
    sendToServer(r);
}

void Communication::stopCall()
{
    Request r(Request::STOPCALL, "", token);
    sendToServer(r);
}

void Communication::addFriend(std::string name)
{
    Request r(Request::ADDFRIEND, name, token);
    sendToServer(r);
}

void Communication::removeFriend(std::string name)
{
    Request r(Request::REMOVEFRIEND, name, token);
    sendToServer(r);
}

std::vector<std::string> Communication::getFriends()
{
    Request r(Request::GETFRIENDS, "", token);
    sendToServer(r);
}

std::vector<std::string> Communication::getFriendRequests()
{
    Request r(Request::GETFRIENDREQUESTS, "", token);
    sendToServer(r);
}

void Communication::acceptFriendRequest(std::string name)
{
    Request r(Request::ACCEPTFRIENDREQUEST, name, token);
    sendToServer(r);
}

bool Communication::connectUser(std::string name, std::string password)
{
    Request r(Request::CONNECT, name + "," + password, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATEUSER) {
        token = lastRequestRecieve.getRequestContent();
        return (true);
    } else
        return (false);
}

void Communication::disconnect()
{
    Request r(Request::DISCONNECT, "", token);
    sendToServer(r);
}

vostd::map<std::string, std::vector<std::string>>id Communication::parse()
{
    std::string content = lastRequestRecieve.getRequestContent();
    std::map<std::string, std::vector<std::string>> team;
    std::vector<std::string> members;
    std::string name;

    for (; content != "";) {
        if (content[0] == ';')
            content.erase(0, 1);
        name = content.substr(0, content.find("("));
        size_t pos = content.find(name);
        if (pos != std::string::npos)
            content.erase(pos, name.length() + 1);
        for (; content[0] != ')';) {
            if (content[0] == ',')
                content.erase(0, 1);
            if (content.find(",") < content.find(")"))
                members.push_back(content.substr(0, content.find(",")));
            else
                members.push_back(content.substr(0, content.find(")")));
            pos = content.find(members.back());
            if (pos != std::string::npos)
                content.erase(pos, members.back().length());
        }
        team.insert(std::make_pair(name, members));
        members.clear();
        if (content[0] == ')')
            content.erase(0, 1);
    }
    return (team);
}

std::map<std::string, std::vector<std::string>> Communication::getTeams()
{
    Request r(Request::GETTEAMS, "", token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDGETTEAMS)
        return (parse());
    else {
        
    }
}

void Communication::callTeam(std::string name)
{
    Request r(Request::CALLTEAM, name, token);
    sendToServer(r);
}

void Communication::getCallTeam(std::string name)
{

}

void Communication::addUserToTeam(std::string name)
{
    Request r(Request::ADDUSERTOTEAM, name, token);
    sendToServer(r);
}

void Communication::acceptTeamRequest(std::string name)
{
    Request r(Request::ACCEPTTEAMREQUEST, name, token);
    sendToServer(r);
}

bool Communication::changeName(std::string name)
{
    Request r(Request::CHANGENAME, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCHANGENAME)
        return (true);
    else
        return (false);
}
