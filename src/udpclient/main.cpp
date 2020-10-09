#include <QCoreApplication>
#include "myudp.hpp"
#include "../PortAudio/PortAudio.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyUDP client;

    client.HelloUDP();

    return a.exec();
}