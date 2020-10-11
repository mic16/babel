/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** tcpConnection
*/
/** @file */
#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ServerLogic.hpp"
#include "../utils/Request.hpp"
#include "../utils/Utils.hpp"

class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
{
    public:
        typedef boost::shared_ptr<TcpConnection> pointer;

        static pointer create(boost::asio::io_service& ios);
        boost::asio::ip::tcp::socket& socket();
        void start();

    private:	
        TcpConnection(boost::asio::io_service& ioService, ServerLogic *logic);
        void handleWrite(const boost::system::error_code& error);
        void handleRead(const boost::system::error_code& error);
        void handleReadHeader(const boost::system::error_code& error);
        boost::asio::ip::tcp::socket mSocket;
        std::string mMessage;
        boost::array<unsigned char, 4> bufForSize;
        char *buf;
        ServerLogic *logic;
};
#endif /* !TCPCONNECTION_HPP_ */
