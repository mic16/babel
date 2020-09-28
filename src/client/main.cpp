/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include <iostream>
#include <stdio.h>
// #include <opus/opus.h>
// #include <portaudio.h>
// #include <QtWidgets>
// #include <QMainWindow>
// #include <QDesktopWidget>
// #include <QFrame>
// #include <QFont>
// #include <QLine>
#include <boost/asio.hpp>
// #include "LineWidget.hpp"

// void create_menu(QMainWindow *mainWindow)
// {
// 	QMenuBar menu = mainWindow->menuBar();
// 	QMenu actionFile = menu->addMenu(tr("&File"));
// 	actionFile->addAction("newAct");


// }

// int main(int argc, char **argv)
// {
// 	QApplication app (argc, argv);
// 	QMainWindow mainWindow;
// 	QDesktopWidget dw;
// 	QLabel label ("Babel", &mainWindow);
// 	QFont font("Arial", 50, QFont::Bold);
// 	LineWidget myWidget(QLine(0, 100, 1400, 100), &mainWindow);
// 	LineWidget myWidget2(QLine(100, 0, 100, 1400), &mainWindow);

// 	mainWindow.setCentralWidget(&myWidget);
// 	// mainWindow.setCentralWidget(&myWidget2);

// 	if (app.setStyle("windows") == nullptr)
// 		std::cout << "Style error" << std::endl;

// 	int x=dw.width()*0.7;
// 	int y=dw.height()*0.7;
// 	mainWindow.setFixedSize(x,y);
// 	mainWindow.show();

// 	myWidget.show();
// 	myWidget2.show();

// 	label.setFont(font);
// 	label.show();

// 	return app.exec();
// }



int main() {
     boost::asio::io_service io_service;
//socket creation
     boost::asio::ip::tcp::socket socket(io_service);
//connection
     socket.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
// request/message from client
     const std::string msg = "Hello from Client!\n";
     boost::system::error_code error;
     boost::asio::write( socket, boost::asio::buffer(msg), error );
     if( !error ) {
        std::cout << "Client sent hello message!" << std::endl;
     }
     else {
        std::cout << "send failed: " << error.message() << std::endl;
     }
 // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof ) {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << data << std::endl;
    }
    return 0;
}
