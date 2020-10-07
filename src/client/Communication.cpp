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
    Request r(Request::CREATETEAM, teamName);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATETEAM)
        return (true);
    else
        return (false);
}

void Communication::callUser(std::string name)
{
    Request r(Request::CALLUSER, name);
    sendToServer(r);
}

void Communication::getCall(std::string name)
{

}

void Communication::acceptCall()
{
    Request r(Request::ACCEPTCALL);
    sendToServer(r);
}

void Communication::stopCall()
{
    Request r(Request::STOPCALL);
    sendToServer(r);
}


void Communication::addFriend(std::string name)
{
    Request r(Request::ADDFRIEND);
    sendToServer(r);
}

void Communication::removeFriend(std::string name)
{
    Request r(Request::REMOVEFRIEND);
    sendToServer(r);
}

std::vector<std::string> Communication::getFriends()
{
    Request r(Request::GETFRIENDS);
    sendToServer(r);
}

std::vector<std::string> Communication::getFriendRequests()
{
    Request r(Request::GETFRIENDREQUESTS);
    sendToServer(r);
}

void Communication::acceptFriendRequest(std::string name)
{
    Request r(Request::ACCEPTFRIENDREQUEST);
    sendToServer(r);
}

bool Communication::connectUser(std::string name, std::string password)
{
    Request r(Request::CONNECT);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATEUSER) {
        token = lastRequestRecieve.getRequestContent();
        return (true);
    } else
        return (false);
}

void Communication::disconnect()
{
    Request r(Request::DISCONNECT);
    sendToServer(r);
}

void Communication::parse()
{

}

std::map<std::string, std::vector<std::string>> Communication::getTeams()
{
    Request r(Request::GETTEAMS);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDGETTEAMS) {
        parse();
    }
}

void Communication::callTeam(std::string name)
{
    Request r(Request::CALLTEAM);
    sendToServer(r);
}

void Communication::getCallTeam(std::string name)
{
    Request r(Request::GETCALLTEAM);
    sendToServer(r);
}

void Communication::addUserToTeam(std::string name)
{
    Request r(Request::ADDUSERTOTEAM);
    sendToServer(r);
}

void Communication::acceptTeamRequest(std::string name)
{
    Request r(Request::ACCEPTTEAMREQUEST);
    sendToServer(r);
}

bool Communication::changeName(std::string name)
{
    Request r(Request::CHANGENAME);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCHANGENAME)
        return (true);
    else
        return (false);
}
