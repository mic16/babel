// /*
// ** EPITECH PROJECT, 2020
// ** Visual Studio Live Share (Workspace)
// ** File description:
// ** Epitech File
// */

// #include <iostream>
// #include <stdio.h>
// #include <opus/opus.h>
// #include <portaudio.h>
// #include <QtWidgets>
// #include <QMainWindow>
// #include <QDesktopWidget>
// #include <QFrame>
// #include <QFont>
// #include <QLine>
// #include <portaudio.h>

// int main(int argc, char **argv)
// {
// 	QApplication app (argc, argv);
// 	QMainWindow mainWindow;
// 	QDesktopWidget dw;
// 	// QLabel label ("Babel", &mainWindow);
// 	// QFont font("Arial", 50, QFont::Bold);
// 	// LineWidget myWidget(QLine(0, 100, 1400, 100), &mainWindow);
// 	// LineWidget myWidget2(QLine(100, 0, 100, 1400), &mainWindow);

// 	// mainWindow.setCentralWidget(&myWidget);

// 	// if (app.setStyle("windows") == nullptr)
// 	// 	std::cout << "Style error" << std::endl;

// 	int x=dw.width()*0.7;
// 	int y=dw.height()*0.7;
// 	mainWindow.setFixedSize(x,y);
// 	mainWindow.show();

// 	// myWidget.show();
// 	// myWidget2.show();

// 	// label.setFont(font);
// 	// label.show();

// 	// Pa_Initialize();
//     // Pa_Terminate();
// 	// std::cout << "YOO les boys" << std::endl;
//     // return 0;
// 	return app.exec();
// }

// #include <QCoreApplication>
// #include "Server.hpp"

// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);

//     // Create an instance of a server and then start it.
//     MyServer Server;
//     Server.StartServer();
    
//     return a.exec();
// }

// #include <portaudio.h>
// #include <iostream>

// int main()
// {
//     Pa_Initialize();
//     Pa_Terminate();
//     std::cout << "YOO les boys" << std::endl;
//     return 0;
// }

#include "Communication.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Communication *c = new Communication();
    QMainWindow w;
	
	c->parse();

    w.show();

    return a.exec();
}