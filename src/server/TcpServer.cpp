/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

TcpServer::TcpServer(boost::asio::io_service& io_service, int port)
    : mAcceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    startAccept();
}
            
void TcpServer::startAccept()
{
    TcpConnection::pointer newConnection = TcpConnection::create(static_cast<boost::asio::io_context&>(mAcceptor.get_executor().context()));

    mAcceptor.async_accept(newConnection->socket(),
        boost::bind(&TcpServer::handleAccept, this, newConnection,
        boost::asio::placeholders::error));
}
    
void TcpServer::handleAccept(TcpConnection::pointer newConnection, const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Reçu un client!" << std::endl;
        newConnection->start();
        startAccept();
    }
}