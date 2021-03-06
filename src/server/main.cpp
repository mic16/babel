/*
** EPITECH PROJECT, 2020
** B-CPP-500-MPL-5-1-babel-yoan.vessiere
** File description:
** main
*/
/** @file */
#include "main.hpp"

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