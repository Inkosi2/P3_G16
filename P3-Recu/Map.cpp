#include "Map.h"
#include "Renderer.hh"
#include "Player.h"
#include <fstream>


Map::Map()
{
	std::ifstream fentrada("default.cfg", std::ios::out);

	for (int j = 0; j < heightMap; j++)
	{
		for (int i = 0; i < widthMap; i++)
		{
			fentrada >> mapArray[j][i];
		}
	}

	for (int j = 0; j < heightMap; j++)
	{
		for (int i = 0; i < widthMap; i++)
		{
			defaultMap[j][i] = mapArray[j][i];

			if (defaultMap[j][i] == '.' || defaultMap[j][i] == ':' || defaultMap[j][i] == 'X' || defaultMap[j][i] == 'O')
			{
				defaultMap[j][i] = mapArray[j][i];
			}
			else
			{
				defaultMap[j][i] = '.';
			}
		}
	}
	fentrada.close();
}

void Map::printMap()
{
	system("cls");

	enti::cout << enti::endl << "  ";

	for (int j = 0; j < heightMap; j++)
	{
		for (int i = 0; i < widthMap; i++)
		{
			if (mapArray[j][i] == 'X')
				enti::cout << enti::Color::LIGHTRED << mapArray[j][i];
			else if (mapArray[j][i] == 'O')
				enti::cout << enti::Color::LIGHTBLUE << mapArray[j][i];
			else if (mapArray[j][i] == ':')
				enti::cout << enti::Color::LIGHTGREEN << mapArray[j][i];
			else if (mapArray[j][i] == '.')
				enti::cout << enti::Color::BROWN << mapArray[j][i];
			else
				enti::cout << enti::Color::WHITE << mapArray[j][i];
		}
		enti::cout << enti::endl << "  ";
	}
	enti::cout << enti::cend;
}


Map::~Map()
{
}
