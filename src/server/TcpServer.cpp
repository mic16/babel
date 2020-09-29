/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

TcpServer::TcpServer(boost::asio::io_service& io_service, int port)
    : m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    start_accept();
}
            
void TcpServer::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(static_cast<boost::asio::io_context&>(m_acceptor.get_executor().context()));

    m_acceptor.async_accept(new_connection->socket(),
        boost::bind(&TcpServer::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}
    
void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Reçu un client!" << std::endl;
        new_connection->start();
        start_accept();
    }
}