#include <QCoreApplication>
#include "myudp.hpp"
// #include "../PortAudio/PortAudioRecord.hpp"

int main(int argc, char *argv[])
{
    PortAudioRecord *audio = new PortAudioRecord();

    while (1)
        this->Start();

    return (0);

    // QCoreApplication a(argc, argv);
    // MyUDP client;

    // if (argc > 1)
    //     client.HelloUDP();
    // return a.exec();
}