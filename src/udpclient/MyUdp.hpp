#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <vector>
#include <iostream>
#include <cstring>


class MyUdp : public QObject
{
    Q_OBJECT
public:
    explicit MyUdp(QObject *parent = 0);
    void readyRead();
    void write(const float *inputSamples, unsigned long samplesCount);
    void read(float *outputSamples, unsigned long samplesCount);
    void setFriend(QHostAddress adresse);

signals:

public slots:

private:
    std::vector<QByteArray> stock;
    QHostAddress adresse;
    QUdpSocket *socket;

};

#endif // MYUDP_H