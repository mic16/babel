/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Epitech File
*/

#include "main.hpp"

// int main (){
// 	Request r(Request::CONNECT, "abricot", "judaisme");
// 	std::cout << r.getRequestType() << "/" << r.getRequestToken() << "/" << r.getRequestContent() << std::endl;

// 	Request q(((r.getRequestToSend().c_str()) + 4));
// 	std::cout << q.getRequestType() << "/" << q.getRequestToken() << "/" << q.getRequestContent() << std::endl;
// }


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


	std::string content = Request(Request::CONNECT, "cyril").getRequestToSend();

	while (1)
	{
		int len;
		boost::system::error_code error;
		// Réception des données, len = nombre d'octets reçus // (4)

        std::copy(content.begin(),content.end(),buf.begin());
		len = socket.write_some(boost::asio::buffer(buf, content.size()), error);

		buf.empty();
		len = socket.read_some(boost::asio::buffer(buf), error);

		Request rep = Request(buf.data() + 4);
		std::cout << "res1 : " << rep.getRequestType() << std::endl;
		std::cout << "Terminé ! 1" << std::endl;
		break;

	}

	// socket.close();
	// socket.connect(endpoint);

	content = Request(Request::CONNECT, "jew").getRequestToSend();
	buf = boost::array<char, 128>();
	while (1)
	{
		int len;
		boost::system::error_code error;
		// Réception des données, len = nombre d'octets reçus // (4)

        std::copy(content.begin(),content.end(),buf.begin());
		len = socket.write_some(boost::asio::buffer(buf, content.size()), error);

		buf.empty();
		len = socket.read_some(boost::asio::buffer(buf), error);

		Request rep = Request(buf.data() + 4);
		std::cout << "res2 : " << rep.getRequestType() << std::endl;
		std::cout << "Terminé ! 2" << std::endl;
		break;
	}
	while (1) {
		
	}
	socket.close();
	return 0;

}
