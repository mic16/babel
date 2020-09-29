/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"

TcpConnection::pointer TcpConnection::create(boost::asio::io_service& ios)
{
    return pointer(new TcpConnection(ios));
}

boost::asio::ip::tcp::socket& TcpConnection::socket()
{
    return m_socket;
}

void TcpConnection::start()
{
    m_message = "Bienvenue sur le serveur!";

    boost::asio::async_write(m_socket, boost::asio::buffer(m_message),
        boost::bind(&TcpConnection::handle_write, shared_from_this(),
        boost::asio::placeholders::error)
        );
}

TcpConnection::TcpConnection(boost::asio::io_service& io_service)
    : m_socket(io_service)
{
}

void TcpConnection::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {

    }
}
