#include "myudp.hpp"

MyUDP::MyUDP(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);

    socket->bind(QHostAddress::LocalHost, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}

void MyUDP::readyRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    
    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    
    qDebug() << "Message from: " << sender.toString(); 
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}