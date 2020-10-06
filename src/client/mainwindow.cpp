#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);
    _socket.connectToHost(QHostAddress("127.0.0.1"), 7171);
    _socket.waitForConnected();
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    // Request r(Request::CONNECT, "mic");
    // QByteArray str(r.getRequestToSend().c_str(), r.getRequestToSend().size());
    // _socket.write(str, r.getRequestToSend().size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    QByteArray str = _socket.read(4);
    QByteArray rep = _socket.read(Utils::convertBytesArrayToSizeT(reinterpret_cast<unsigned char *>(str.data())));

    Request r(rep.data());
    std::cout << r.getRequestType() << ":" << r.getRequestContent() << std::endl;
}