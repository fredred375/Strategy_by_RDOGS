#pragma once

<<<<<<< HEAD
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-network-d.lib")

#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cmath>

int main()
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        printf("listener failed\n");
    }

    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        printf("accept failed\n");
    }
=======
#include "Server.h"

int main()
{
	Server server;

	server.run();

	return 0;
>>>>>>> socket
}