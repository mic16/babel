/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "../utils/Utils.hpp"
#include "../utils/Request.hpp"

int main()
{
	// Création du service principal et du résolveur.
	boost::asio::io_service ios;

	// On veut se connecter sur la machine locale, port 7171
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

	// On crée une socket // (1)
	boost::asio::ip::tcp::socket socket(ios);

	// Tentative de connexion, bloquante // (2)
	socket.connect(endpoint);

	// Création du buffer de réception // (3)
	boost::array<char, 128> buf;


	std::string content = Request(Request::CREATEUSER, "mic").getRequestToSend();

	while (1)
	{
		int len;
		boost::system::error_code error;
		// Réception des données, len = nombre d'octets reçus // (4)

        std::copy(content.begin(),content.end(),buf.begin());
		len = socket.write_some(boost::asio::buffer(buf, content.size()), error);

		buf.empty();
		len = socket.read_some(boost::asio::buffer(buf), error);

		if (error == boost::asio::error::eof) // (5)
		{
			std::cout << "\nTerminé !" << std::endl;
			break;
		}
		Request rep = Request(buf.data() + 4);
		// On affiche (6)
		std::cout << "res :";
		std::cout.write(buf.data(), len); 
	}
	return 0;
}
