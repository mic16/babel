#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include "portaudio.h"
#include "../PortAudio/PortAudioRecord.hpp"

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    void HelloUDP();
signals:

public slots:
    void readyRead();

private:
    PortAudio *audio;
    QUdpSocket *socket;

};

#endif // MYUDP_H