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

bool Communication::callUser(std::string name)
{
    Request r(Request::CALLUSER, name);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCALLUSER)
        return (true);
    else
        return (false);
}

bool Communication::getCall(std::string name)
{

}

bool Communication::acceptCall()
{
    Request r(Request::ACCEPTCALL);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTCALL)
        return (true);
    else
        return (false);
}

bool Communication::stopCall()
{
    Request r(Request::STOPCALL);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDSTOPCALL)
        return (true);
    else
        return (false);
}


bool Communication::addFriend(std::string name)
{
    Request r(Request::ADDFRIEND);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDADDFRIEND)
        return (true);
    else
        return (false);
}

bool Communication::removeFriend(std::string name)
{
    Request r(Request::REMOVEFRIEND);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDREMOVEFRIEND)
        return (true);
    else
        return (false);
}

std::vector<std::string> Communication::getFriends()
{
    Request r(Request::GETFRIENDS);
    std::string delim = ",";
    std::vector<std::string> vec;

    if (lastRequestRecieve.getRequestType() == Request::VALIDGETFRIENDS) {
        std::string str = lastRequestRecieve.getRequestContent();
        while (str.find(delim) != std::string::npos) {
            vec.push_back(str.substr(0, str.find(delim)));
            str.erase(0, str.substr(0, str.find(delim)).length() + delim.length());
        }
        vec.push_back(str);
    } else {
        vec.push_back("error");
    }
    sendToServer(r);
    return (vec);
}

std::vector<std::string> Communication::getFriendRequests()
{
    Request r(Request::GETFRIENDREQUESTS);
    std::string delim = ",";
    std::vector<std::string> vec;

    if (lastRequestRecieve.getRequestType() == Request::VALIDGETFRIENDREQUESTS) {
        std::string str = lastRequestRecieve.getRequestContent();
        while (str.find(delim) != std::string::npos) {
            vec.push_back(str.substr(0, str.find(delim)));
            str.erase(0, str.substr(0, str.find(delim)).length() + delim.length());
        }
        vec.push_back(str);
    } else {
        vec.push_back("error");
    }
    sendToServer(r);
    return (vec);
}

bool Communication::acceptFriendRequest(std::string name)
{
    Request r(Request::ACCEPTFRIENDREQUEST);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTFRIENDREQUEST)
        return (true);
    else
        return (false);
}

bool Communication::connectUser(std::string name, std::string password)
{
    Request r(Request::CONNECT);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCONNECT) {
        token = lastRequestRecieve.getRequestContent();
        return (true);
    } else
        return (false);
}

bool Communication::disconnect()
{
    Request r(Request::DISCONNECT);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDDISCONNECT)
        return (true);
    else
        return (false);
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

bool Communication::callTeam(std::string name)
{
    Request r(Request::CALLTEAM);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCALLTEAM)
        return (true);
    else
        return (false);
}

bool Communication::getCallTeam(std::string name)
{

}

bool Communication::addUserToTeam(std::string name)
{
    Request r(Request::ADDUSERTOTEAM);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDADDUSERTOTEAM)
        return (true);
    else
        return (false);
}

bool Communication::acceptTeamRequest(std::string name)
{
    Request r(Request::ACCEPTTEAMREQUEST);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTTEAMREQUEST)
        return (true);
    else
        return (false);
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
