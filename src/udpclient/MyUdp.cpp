/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** tcpServer
*/
/** @file */
#include "MyUdp.hpp"

MyUdp::MyUdp(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void MyUdp::setFriend(QHostAddress adresse)
{
    this->adresse = adresse;
}

void MyUdp::write(const float *inputSamples, unsigned long samplesCount)
{
    int size = samplesCount * sizeof(float);
    QByteArray data;
    data.append(reinterpret_cast<const char *>(inputSamples), size);
    socket->writeDatagram(data, size, adresse, 1234);
}

void MyUdp::handleReadyRead()
{
    QByteArray buffer;
    buffer.resize(512 * sizeof(float));
    
    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), 512 * sizeof(float), &sender, &senderPort);
    stock.push_back(buffer);
}

void MyUdp::read(float *outputSamples, unsigned long samplesCount)
{
    std::memset(outputSamples, 0, samplesCount * sizeof(float));
    if (stock.size() > 0) {
        QByteArray buffer = stock[0];
        std::memcpy(outputSamples, stock[0].data(), samplesCount * sizeof(float));
        stock.erase(stock.begin());
    }
}