#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#include "Game.h"

int main()
{
	int teamIDInput = 0;
	std::string ipInput;
	while (!(teamIDInput >= 1 && teamIDInput <= numTeams))
	{
		printf("Enter team ID: ");
		std::cin >> teamIDInput;
		if (!(teamIDInput >= 1 && teamIDInput <= numTeams))
		{
			printf("Invalid ID...\n");
		}
	}


	printf("\nEnter server IP: ");

	std::cin >> ipInput;


	Game game(teamIDInput, ipInput);

	game.run();

	return 0;
}