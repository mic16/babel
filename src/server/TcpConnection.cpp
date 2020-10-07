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
    mSocket.async_read_some(boost::asio::buffer(bufForSize, 4), boost::bind(&TcpConnection::handleReadHeader, shared_from_this(),
        boost::asio::placeholders::error));
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
        Request request = this->logic->executeLogic(Request(buf), this);
        mMessage = request.getRequestToSend();
        boost::asio::async_write(mSocket, boost::asio::buffer(mMessage),
            boost::bind(&TcpConnection::handleWrite, shared_from_this(),
            boost::asio::placeholders::error)
            );
    }
    this->start();
}