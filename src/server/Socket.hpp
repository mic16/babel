/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class Socket {
    private:
        boost::asio::ip::tcp::socket sock;
        std::string message="Hello From Socket!";
        enum { max_length = 1024 };
        char data[max_length];
    public:
        typedef boost::shared_ptr<Socket> pointer;
        Socket(boost::asio::io_service& io_service);
        static pointer create(boost::asio::io_service& io_service);
        boost::asio::ip::tcp::socket& socket();
        void start();

    protected:
};

#endif /* !SOCKET_HPP_ */
