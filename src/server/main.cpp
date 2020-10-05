#include "mainwindow.hpp"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    // std::cout << "server up\n";
    QApplication a(argc, argv);
    // std::cout << "server up\n";
    MainWindow w;
    w.show();

    return a.exec();
}