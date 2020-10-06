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

bool createUser(std::string name, std::string password)
{
    Request r(Request::CREATEUSER, name, password);
    QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    _socket.write(str, r.getRequestToSend().size());
}

bool createTeam(std::map<std::string, std::vector<std::string>> team)
{
    Request r(Request::CREATEUSER, name, password);
    QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    _socket.write(str, r.getRequestToSend().size());
}

void callUser(std::string name);
void getCall(std::string name);
void acceptCall();
void stopCall();

void addFriend(std::string name);
void removeFriend(std::string name);
std::vector<std::string> getFriends(); // Yoan en a pas
std::vector<std::string> getFriendRequests();
void acceptFriendRequest(std::string name);

std::string connect(std::string name, std::string password);
void disconnect();

std::map<std::string, std::vector<std::string>> getTeams();
void callTeam(std::string name);
void getCallTeam(std::string name);
void addUserToTeam(std::string name);
void acceptTeamRequest(std::string name);

bool changeName(std::string name);