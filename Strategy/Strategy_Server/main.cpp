#pragma once


#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

#include <iostream>
#include <vector>
#include <string>

const unsigned short port = 2000;

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	std::cout << ip.toString() << std::endl;
	sf::TcpSocket socket;
	char type, mode, buffer[1000];

	std::size_t bytesRecieved;

	std::string text = "connected to: ";
	
	std::cin >> type;

	if (type == 's')
	{
		sf::TcpListener listener;
		listener.listen(port);
		listener.accept(socket);

		text += "server";
	}
	else if (type == 'c')
	{
		socket.connect(ip, port);

		text += "client";
	}

	socket.send(text.c_str(), text.length() + 1);

	socket.receive(buffer, sizeof(buffer), bytesRecieved);

	std::cout << buffer << std::endl;

	system("pause");
	return 0;
}