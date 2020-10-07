#include <QCoreApplication>
#include "myudp.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    MyUDP client;

    if (argc > 1)
        client.HelloUDP();    
    return a.exec();
}