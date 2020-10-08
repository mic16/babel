#include <QCoreApplication>
#include "Udpclient.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    UDPClient client;

    if (argc > 1)
        client.HelloUDP();    
    return a.exec();
}