#include "MyUdp.hpp"

MyUdp::MyUdp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUdp::setFriend(QHostAddress adresse)
{
    this->adresse = adresse;
    socket->bind(adresse, 1234);
}

void MyUdp::write(const float *inputSamples, unsigned long samplesCount)
{
    int size = samplesCount * sizeof(float);
    QByteArray data;
    data.append(reinterpret_cast<const char *>(inputSamples), size);
    socket->writeDatagram(data, size, adresse, 1234);
}

void MyUdp::readyRead()
{
    QByteArray buffer;
    buffer.resize(512 * sizeof(float));
    
    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), 512 * sizeof(float), &sender, &senderPort);
    stock = buffer;
}

const float *MyUdp::read(unsigned long samplesCount)
{
    return (reinterpret_cast<const float *>(stock.data()));
}