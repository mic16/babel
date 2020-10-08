#include "Udpclient.hpp"

UDPClient::UDPClient()
{
    
}

UDPClient::UDPClient(std::string addresseIP, QObject *parent) : QObject(parent)
{
    audio.Start();
    socket = new QUdpSocket(this);
    this->addresseIP = QString::fromStdString(addresseIP);

    socket->bind(QHostAddress(this->addresseIP), 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

UDPClient::~UDPClient()
{

}

void UDPClient::sendAcceptCall(Request r)
{
    QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    socket->write(str, r.getRequestToSend().size());
}

void UDPClient::HelloUDP()
{
    while (1) {
        QByteArray Data;
        PaStream *d = audio.Record();
        Data.append(static_cast<char *>(d), 10240);
        socket->writeDatagram(Data, 10240, QHostAddress(this->addresseIP), 1234);
    }
}

void UDPClient::readyRead()
{
    QByteArray buffer;
    buffer.resize(10240);
    
    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), 10240, &sender, &senderPort);
    
    audio.Play(static_cast<PaStream *>(buffer.data()));
    qDebug() << "Message from: " << sender.toString(); 
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}