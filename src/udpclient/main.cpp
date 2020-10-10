#include <QCoreApplication>
#include "myudp.hpp"
#include "../PortAudio/PortAudioRecord.hpp"

int main(int argc, char *argv[])
{
    PortAudio *audio = new PortAudio();

    while (1)
        audio->Start();

    return (0);

    // QCoreApplication a(argc, argv);
    // MyUDP client;

    // if (argc > 1)
    //     client.HelloUDP();
    // return a.exec();
}