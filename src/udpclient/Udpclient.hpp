#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include "PortAudioRecord.hpp"
#include "../utils/Request.hpp"

class UDPClient : public QObject {

    Q_OBJECT

public:
    explicit UDPClient();
    explicit UDPClient(std::string addresseIP, QObject *parent = 0);
    ~UDPClient();
    void HelloUDP();
    void sendAcceptCall(Request r);
signals:
    
public slots:
    void readyRead();

private:
    PortAudioRecord audio;
    QUdpSocket *socket;
    QString addresseIP;
    
};

#endif // UDPCLIENT_H