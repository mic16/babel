/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** tcpServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "TcpConnection.hpp" 

class TcpServer
{
	public:
		TcpServer(boost::asio::io_service& io_service, int port);
					
	private:
		void start_accept();
		void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
						
		boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif /* !TCPSERVER_HPP_ */
