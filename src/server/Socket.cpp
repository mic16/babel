/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** Socket
*/

#include "Socket.hpp"

class Socket : public boost::enable_shared_from_this<Socket>
{

    Socket(boost::asio::io_service& io_service) : sock(io_service)
    {

    }

    static boost::shared_ptr<Socket> create(boost::asio::io_service& io_service)
    {
        return boost::shared_ptr<Socket>(new Socket(io_service));
    }

    boost::asio::ip::tcp::socket& socket()
    {
        return sock;
    }

    void start()
    {
        sock.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(&Socket::handle_read,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));

        sock.async_write_some(
            boost::asio::buffer(message, max_length),
            boost::bind(&Socket::handle_write,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err) {
                cout << data << endl;
        } else {
                std::cerr << "error: " << err.message() << std::endl;
                sock.close();
        }
    }

    void handle_write(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err) {
            cout << "Socket sent Hello message!"<< endl;
        } else {
            std::cerr << "error: " << err.message() << endl;
            sock.close();
        }
    }
};