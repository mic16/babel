/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** main
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "TcpServer.hpp"

int main()
{
	try
	{
		boost::asio::io_service io_service;
		
		// Création d'un serveur
		TcpServer server(io_service, 7171);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
			
	return 0;
}