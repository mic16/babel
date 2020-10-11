#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <vector>


class MyUdp : public QObject
{
    Q_OBJECT
public:
    explicit MyUdp(QObject *parent = 0);
    void readyRead();
    void write(const float *inputSamples, unsigned long samplesCount);
    const float *read(unsigned long samplesCount);
    void setFriend(QHostAddress adresse);

signals:

public slots:

private:
    QByteArray stock;
    QHostAddress adresse;
    QUdpSocket *socket;

};

#endif // MYUDP_H