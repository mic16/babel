#include "Communication.hpp"

Communication::Communication()
{
    connectToServer();
}

Communication::~Communication()
{

}

std::string Communication::getUserIP()
{
    return (userIP);
}

void Communication::connectToServer()
{
    _socket.connectToHost(QHostAddress("127.0.0.1"), 7171);
    if (_socket.waitForConnected())
        connected = true;
    else
        connected = false;
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

bool Communication::isServerOn()
{
    return (connected);
}

bool Communication::createUser(std::string name, std::string password)
{
    Request r(Request::CREATEUSER, name + "," + password);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCREATEUSER) {
        token = lastRequestRecieve.getRequestContent();
        return (true);
    } else
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

bool Communication::callUser(std::string name)
{
    Request r(Request::CALLUSER, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCALLUSER) {
        userIP = lastRequestRecieve.getRequestContent();
        return (true);
    } else
        return (false);
}

bool Communication::hangUpFriend()
{
    Request r(Request::STOPCALL, "", token);
    sendToServer(r);
    if (lastRequestRecieve.getRequestType() == Request::VALIDSTOPCALL)
        return (true);
    else
        return (false);
}

std::string Communication::getCall()
{
    Request r(Request::GETCALL, "", token);
    sendToServer(r);
    if (lastRequestRecieve.getRequestType() == Request::VALIDGETCALL && lastRequestRecieve.getRequestContent().length() > 0) {
        std::vector<std::string> vec;
        boost::split(vec, lastRequestRecieve.getRequestContent(), boost::is_any_of(","));
        std::string name = vec[0];
        userIP = vec[1];
        return (name);
    } else
        return ("");
}

bool Communication::acceptCall(bool response)
{
    Request r(Request::ACCEPTCALL, (response ? "ACCEPT" : "REFUSE"),token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTCALL)
        return (true);
    else
        return (false);
}

bool Communication::stopCall()
{
    Request r(Request::STOPCALL, "", token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDSTOPCALL)
        return (true);
    else
        return (false);
}

int Communication::getAcceptCall()
{
    Request r(Request::GETACCEPTCALL, "", token);
    sendToServer(r);
    if (lastRequestRecieve.getRequestType() == Request::VALIDGETACCEPTCALL) {
        if (lastRequestRecieve.getRequestContent().compare("WAIT"))
            return (-1);
        if (lastRequestRecieve.getRequestContent().compare("ACCEPT"))
            return (0);
        if (lastRequestRecieve.getRequestContent().compare("REFUSE"))
            return (1);
    }
    return (-2);
}

bool Communication::addFriend(std::string name)
{
    Request r(Request::ADDFRIEND, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDADDFRIEND)
        return (true);
    else
        return (false);
}

bool Communication::removeFriend(std::string name)
{
    Request r(Request::REMOVEFRIEND, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDREMOVEFRIEND)
        return (true);
    else
        return (false);
}

std::vector<std::string> Communication::getFriends()
{
    Request r(Request::GETFRIENDS, "", token);
    std::string delim = ",";
    std::vector<std::string> vec;

    sendToServer(r);
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
    return (vec);
}

std::vector<std::string> Communication::getFriendRequests()
{
    Request r(Request::GETFRIENDREQUESTS, "", token);
    std::string delim = ",";
    std::vector<std::string> vec;

    sendToServer(r);
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
    return (vec);
}

bool Communication::acceptFriendRequest(std::string name)
{
    Request r(Request::ACCEPTFRIENDREQUEST, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTFRIENDREQUEST)
        return (true);
    else
        return (false);
}

bool Communication::connectUser(std::string name, std::string password)
{
    Request r(Request::CONNECT, name + "," + password, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCONNECT) {
        token = lastRequestRecieve.getRequestContent();
        return (true);
    } else
        return (false);
}

bool Communication::disconnect()
{
    Request r(Request::DISCONNECT, "", token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDDISCONNECT)
        return (true);
    else
        return (false);
}

std::map<std::string, std::vector<std::string>> Communication::parse()
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
        std::map<std::string, std::vector<std::string>> team;
        std::vector<std::string> tmp;
        team.insert(std::make_pair("Error", tmp));
        return (team);
    }
}

bool Communication::callTeam(std::string name)
{
    Request r(Request::CALLTEAM, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDCALLTEAM)
        return (true);
    else
        return (false);
}

bool Communication::getCallTeam(std::string name)
{

}

bool Communication::addUserToTeam(std::string userName, std::string teamName)
{
    Request r(Request::ADDUSERTOTEAM, teamName + "," + userName, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDADDUSERTOTEAM)
        return (true);
    else
        return (false);
}

bool Communication::removeUserFromTeam(std::string userName, std::string teamName)
{
    Request r(Request::REMOVEUSERFROMTEAM, teamName + "," + userName, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDREMOVEUSERFROMTEAM)
        return (true);
    else
        return (false);
}

bool Communication::acceptTeamRequest(std::string name)
{
    Request r(Request::ACCEPTTEAMREQUEST, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDACCEPTTEAMREQUEST)
        return (true);
    else
        return (false);
}

bool Communication::destroyTeam(std::string name)
{
    Request r(Request::DESTROYTEAM, name, token);
    sendToServer(r);

    if (lastRequestRecieve.getRequestType() == Request::VALIDDESTROYTEAM)
        return (true);
    else
        return (false);
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
