#include "Map.h"
#include "Renderer.hh"
#include "Player.h"
#include "Input.hh"
#include <fstream>
#include <iostream>


void main()
{
	bool game = false;
	bool gameEnd = false;
	int gameEndInt = 0;

	if (!game)
	{
		std::cout << std::endl;

		std::cout << "  Welcome to CLASH OF ENTIOS";
		for (int i = 0; i < 5; i++)
		{
			std::cout << std::endl;
		}

		std::cout << "  Press ENTER to start the game...";

		enti::InputKey key1 = enti::InputKey::NONE;

		while (key1 != enti::InputKey::ENTER)
		{
			key1 = enti::getInputKey();
		}

		game = true;
	}

	if (game)
	{
		//Creamos el mapa de la clase Map y el players de tipo Player
		Map map;
		Player players;
		players.setPlayersData(map);


		//Imprimimos el mapa
		map.printMap();

		players.printPlayersData();

		std::cout << "Remaining Actions: 10" << std::endl;
		std::cout << "Entio: A";
		std::cout << "\n" << "Team playing: 0";

		//Creamos la variable de tipo InputKey
		while (!gameEnd)
		{
			enti::InputKey key;

			key = enti::getInputKey();

			players.actionsEntio(key);

			gameEndInt = players.endGame();

			if (gameEndInt == 1 || gameEndInt == 2 || key == enti::InputKey::ESC)
			{
				gameEnd = true;
			}
		}
	}
	if (gameEnd)
	{
		std::cout << "  GAME OVER";

		if (gameEndInt == 1)
		{
			std::cout << "  Team 2 win!";
		}
		else if (gameEndInt == 2)
		{
			std::cout << "  Team 1 win!";
		}
	}
}