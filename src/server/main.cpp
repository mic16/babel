/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** main
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

std::string read_(boost::asio::ip::tcp::socket & socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until( socket, buf, "\n" );
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void send_(boost::asio::ip::tcp::socket & socket, const std::string& message) {
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message) );
}

int main() {

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234 ));
    
    while (true) 
    {
        boost::asio::ip::tcp::socket socket_(io_service);

        acceptor_.accept(socket_);
        std::string message = read_(socket_);
        std::cout << message << std::endl;
        send_(socket_, "Hello From Server!");
        std::cout << "Servent sent Hello message to Client!" << std::endl;
    }
    return 0;
}