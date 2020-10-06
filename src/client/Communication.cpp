#include "Communication.hpp"

Communication::Communication() : _socket(this)
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

void Communication::onReadyRead()
{
    QByteArray str = _socket.read(4);
    QByteArray rep = _socket.read(Utils::convertBytesArrayToSizeT(reinterpret_cast<unsigned char *>(str.data())));

    Request r(rep.data());
    // std::cout << r.getRequestType() << ":" << r.getRequestContent() << std::endl;
}

bool Communication::createUser(std::string name, std::string password)
{
    Request r(Request::CREATEUSER, name + ',' + password);
    QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    _socket.write(str, r.getRequestToSend().size());
    return (true);
}

bool Communication::createTeam(std::map<std::string, std::vector<std::string>> team)
{

}

void Communication::callUser(std::string name)
{

}

void Communication::getCall(std::string name)
{

}

void Communication::acceptCall()
{

}

void Communication::stopCall()
{

}


void Communication::addFriend(std::string name)
{

}

void Communication::removeFriend(std::string name)
{

}

std::vector<std::string> Communication::getFriends()
{

}

std::vector<std::string> Communication::getFriendRequests()
{

}

void Communication::acceptFriendRequest(std::string name)
{

}


std::string Communication::connectUser(std::string name, std::string password)
{

}

void Communication::disconnect()
{

}


std::map<std::string, std::vector<std::string>> Communication::getTeams()
{

}

void Communication::callTeam(std::string name)
{

}

void Communication::getCallTeam(std::string name)
{

}

void Communication::addUserToTeam(std::string name)
{

}

void Communication::acceptTeamRequest(std::string name)
{

}


bool Communication::changeName(std::string name)
{

}
