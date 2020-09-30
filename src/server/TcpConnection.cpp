/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"

TcpConnection::pointer TcpConnection::create(boost::asio::io_service& ios)
{
    return pointer(new TcpConnection(ios, ServerLogic::get()));
}

boost::asio::ip::tcp::socket& TcpConnection::socket()
{
    return mSocket;
}

void TcpConnection::start()
{

    // boost::array<char, 128> buf;
    // boost::system::error_code error;
    // int len = mSocket.read_some(boost::asio::buffer(buf), error);
    // data(new Data);
    mSocket.async_read_some(boost::asio::buffer(bufForSize, 4), boost::bind(&TcpConnection::handleReadHeader, shared_from_this(),
        boost::asio::placeholders::error));
    // mMessage = "Bienvenue sur le serveur!";

    // boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
    //     boost::bind(&TcpConnection::handleWrite, shared_from_this(),
    //     boost::asio::placeholders::error)
    //     );
}

TcpConnection::TcpConnection(boost::asio::io_service& ioService, ServerLogic *logic)
    : mSocket(ioService), logic(logic)
{
}

void TcpConnection::handleWrite(const boost::system::error_code& error)
{
    if (!error)
    {

    }
}

void TcpConnection::handleReadHeader(const boost::system::error_code& error)
{
    if (!error)
    {
        size_t size = Utils::convertBytesArrayToSizeT(bufForSize.data());
        buf = new char[size];
        mSocket.async_read_some(boost::asio::buffer(buf, size), boost::bind(&TcpConnection::handleRead, shared_from_this(),
            boost::asio::placeholders::error));
    }
}

void TcpConnection::handleRead(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << buf << std::endl;
        // TODO : connecter la logique
        mMessage = "Bien Recu !";
        boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
            boost::bind(&TcpConnection::handleWrite, shared_from_this(),
            boost::asio::placeholders::error)
            );
    }
}