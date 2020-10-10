#include "myudp.hpp"

MyUDP::MyUDP(QObject *parent) : QObject(parent)
{
    audio = new PortAudio();
    // audio.Start();
    socket = new QUdpSocket(this);

    socket->bind(QHostAddress::LocalHost, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::HelloUDP()
{
    while (1) {
        QByteArray Data;
        // PaStream *d = audio.Record();
        // Data.append(static_cast<char *>(d), 10240);
        // socket->writeDatagram(Data, 10240, QHostAddress::LocalHost, 1234);
    }
}

void MyUDP::readyRead()
{
    QByteArray buffer;
    buffer.resize(10240);
    
    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), 10240, &sender, &senderPort);
    
    // audio.Play(static_cast<PaStream *>(buffer.data()));
    qDebug() << "Message from: " << sender.toString(); 
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}