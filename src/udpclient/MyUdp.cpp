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
}

void MyUdp::setFriend(QHostAddress adresse)
{
    socket->bind(adresse, 1234);
}

void MyUdp::write(const float *inputSamples, unsigned long samplesCount)
{
    int size = samplesCount * sizeof(float);
    QByteArray data;
    data.append(reinterpret_cast<const char *>(inputSamples), size);
    socket->writeDatagram(data, size, QHostAddress::LocalHost, 1234);
}

const float *MyUdp::read(unsigned long samplesCount)
{
    int size = samplesCount * sizeof(float);
    QByteArray buffer;
    buffer.resize(size);
    socket->readDatagram(buffer.data(), size, nullptr, nullptr);
    return (reinterpret_cast<const float *>(buffer.data()));
}