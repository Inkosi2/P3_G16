#include "Player.h"
#include <stdio.h>
#include <iostream>
#include "Input.hh"
#include "Renderer.hh"
#include <vector>

Player::Player()
{
	currentActions = maxActions;
	currentlyPlayingTeam = team1;
}

void Player::setPlayersData(Map map) //El constructor inicializa la posición y el nombre de cada Entio de la array de Entios
{

	//Inicializamos el nombre de cada Entio,su equipo y las fatigas
	for (int i = 0; i < 6; i++)
	{
		teamA[i].name = 65 + i;
		teamA[i].team = team1;
		teamA[i].exhausment = startingExhausment;
		teamA[i].matchExhausment = startingExhausment;
		teamA[i].turnExhausment = startingExhausment;
		teamA[i].hp = maxHp;
	}
	for (int i = 0; i < 6; i++)
	{
		teamB[i].name = 49 + i;
		teamB[i].team = team2;
		teamB[i].exhausment = startingExhausment;
		teamB[i].matchExhausment = startingExhausment;
		teamB[i].turnExhausment = startingExhausment;
		teamB[i].hp = maxHp;
	}

	//Inicializamos la posición de cada Entio
	findEntioPosition();

}

void Player::findEntioPosition()
{
	for (int k = 0; k < 6; k++)
	{
		for (int j = 0; j < widthMap; j++)
		{
			for (int i = 0; i < heightMap; i++)
			{
				if (map.mapArray[i][j] == teamA[k].name)
				{
					teamA[k].x = i;
					teamA[k].y = j;
				}

				if (map.mapArray[i][j] == teamB[k].name)
				{
					teamB[k].x = i;
					teamB[k].y = j;
				}

			}
		}
	}
}

void Player::orderEntiosByExhausment()
{
	entio aux1;
	entio aux2;


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; i < 5; i++)
		{
			if (teamB[i].hp < 1)
			{
				teamB[i].exhausment = 10000000;
			}
			if (teamB[i].exhausment > teamB[i + 1].exhausment)
			{
				aux1 = teamB[i];
				teamB[i] = teamB[i + 1];
				teamB[i + 1] = aux1;
			}
			else if (teamB[i].exhausment == teamB[i + 1].exhausment)
			{
				aux1 = teamB[i];
				teamB[i] = teamB[i + 1];
				teamB[i + 1] = aux1;
			}
		}
	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; i < 5; i++)
		{
			if (teamA[i].hp < 1)
			{
				teamA[i].exhausment = 10000000;
			}
			if (teamA[i].exhausment > teamA[i + 1].exhausment)
			{
				aux2 = teamA[i];
				teamA[i] = teamA[i + 1];
				teamA[i + 1] = aux2;
			}
			else if (teamA[i].exhausment == teamA[i + 1].exhausment)
			{
				aux2 = teamA[i];
				teamA[i] = teamA[i + 1];
				teamA[i + 1] = aux2;
			}
		}
	}

}

void Player::printPlayersData()
{
	for (int i = 0; i < 38; i++)
	{
		std::cout << "\n";
	}
	std::cout << "Team: A - F" << std::endl;

	for (int i = 0; i < 6; i++)
	{
		if (teamA[i].hp > 1)
		{
			std::cout << teamA[i].name << " // HP: " << teamA[i].hp << " // Fatigue: " << teamA[i].exhausment << " // Arrows: " << teamA[i].arrows << " // Soldier: " << nameList1[i] << std::endl;
		}
		else
		{
			map.mapArray[teamA[i].x][teamA[i].y] = map.defaultMap[teamA[i].x][teamA[i].y];

		}
	}
	std::cout << std::endl << "Team: 1 - 6" << std::endl;

	for (int i = 0; i < 6; i++)
	{

		if (teamB[i].hp > 1)
		{
			std::cout << teamB[i].name << " // HP: " << teamB[i].hp << " // Fatigue: " << teamB[i].exhausment << " // Arrows: " << teamA[i].arrows << " // Soldier: " << nameList2[i] << std::endl;
		}
		else
		{
			map.mapArray[teamB[i].x][teamB[i].y] = map.defaultMap[teamB[i].x][teamB[i].y];
		}
	}

	std::cout << std::endl;
}

void Player::turnManager()
{
	if (currentActions == 0)
	{
		prevEntiosX.clear();
		prevEntiosY.clear();
		if (currentlyPlayingTeam == team1)
		{
			orderEntiosByExhausment();
			currentlyPlayingTeam = team2;
			currentActions = 10;
			orderEntiosByExhausment();

			for (int i = 0; i < 6; i++)
			{
				if (teamA[i].matchExhausment < teamA[i].turnExhausment)
				{
					teamA[i].turnExhausment = 0;
					teamA[i].matchExhausment++;
					teamA[i].exhausment = teamA[i].matchExhausment;
				}
			}
		}
		else if (currentlyPlayingTeam == team2)
		{
			orderEntiosByExhausment();
			currentlyPlayingTeam = team1;
			currentActions = 10;
			orderEntiosByExhausment();

			for (int i = 0; i < 6; i++)
			{
				if (teamB[i].matchExhausment < teamB[i].turnExhausment)
				{
					teamB[i].turnExhausment = 0;
					teamB[i].matchExhausment++;
					teamB[i].exhausment = teamB[i].matchExhausment;
				}
			}
		}
	}
}

void Player::attack(Player::attackDirection currentlyAttackDirection)
{
	int x, y;
	team team;
	weapon weapon;

	if (currentlyPlayingTeam == team1)
	{
		x = teamA[0].x;
		y = teamA[0].y;
		team = teamA[0].team;
		weapon = teamA[0].weapon;
	}
	else if (currentlyPlayingTeam == team2)
	{
		x = teamB[0].x;
		y = teamB[0].y;
		team = teamB[0].team;
		weapon = teamB[0].weapon;
	}

	if (weapon == sword)
	{
		swordAttack(x, y, weapon, currentlyAttackDirection, team);
	}
	else if (weapon == bow)
	{
		bowAttack(x, y, weapon, currentlyAttackDirection, team);

	}
}

void Player::swordAttack(int x, int y, Player::weapon weapon, Player::attackDirection currentlyAttackDirection, Player::team team)
{
	if (currentlyAttackDirection == UP)
	{
		if ((team == team2 && (map.mapArray[x - 1][y] == 'A' || map.mapArray[x - 1][y] == 'B' || map.mapArray[x - 1][y] == 'C' || map.mapArray[x - 1][y] == 'D' || map.mapArray[x - 1][y] == 'E' || map.mapArray[x - 1][y] == 'F')) || (team == team1 && (map.mapArray[x - 1][y] == '1' || map.mapArray[x - 1][y] == '2' || map.mapArray[x - 1][y] == '3' || map.mapArray[x - 1][y] == '4' || map.mapArray[x - 1][y] == '5' || map.mapArray[x - 1][y] == '6')))
		{
			if (team == team2)
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x - 1][y] == teamA[k].name)
					{
						teamA[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}

					}
				}
			}
			else if (team == team1)//                     <-------------------------- Inutil?
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x - 1][y] == teamB[k].name)
					{
						teamB[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
		}
	}
	else if (currentlyAttackDirection == DOWN)
	{
		if ((team == team2 && (map.mapArray[x + 1][y] == 'A' || map.mapArray[x + 1][y] == 'B' || map.mapArray[x + 1][y] == 'C' || map.mapArray[x + 1][y] == 'D' || map.mapArray[x + 1][y] == 'E' || map.mapArray[x + 1][y] == 'F')) || (team == team1 && (map.mapArray[x + 1][y] == '1' || map.mapArray[x + 1][y] == '2' || map.mapArray[x + 1][y] == '3' || map.mapArray[x + 1][y] == '4' || map.mapArray[x + 1][y] == '5' || map.mapArray[x + 1][y] == '6')))
		{
			if (team == team2)
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x + 1][y] == teamA[k].name)
					{
						teamA[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
			else if (team == team1)//                     <-------------------------- Inutil?
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x + 1][y] == teamB[k].name)
					{
						teamB[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
		}
	}
	else if (currentlyAttackDirection == LEFT)
	{
		if ((team == team2 && (map.mapArray[x][y - 1] == 'A' || map.mapArray[x][y - 1] == 'B' || map.mapArray[x][y - 1] == 'C' || map.mapArray[x][y - 1] == 'D' || map.mapArray[x][y - 1] == 'E' || map.mapArray[x][y - 1] == 'F')) || (team == team1 && (map.mapArray[x][y - 1] == '1' || map.mapArray[x][y - 1] == '2' || map.mapArray[x][y - 1] == '3' || map.mapArray[x][y - 1] == '4' || map.mapArray[x][y - 1] == '5' || map.mapArray[x][y - 1] == '6')))
		{
			if (team == team2)
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x][y - 1] == teamA[k].name)
					{
						teamA[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
			else if (team == team1)
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x][y - 1] == teamB[k].name)
					{

						teamB[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
		}
	}

	else if (currentlyAttackDirection == RIGHT)
	{
		if ((team == team2 && (map.mapArray[x][y + 1] == 'A' || map.mapArray[x][y + 1] == 'B' || map.mapArray[x][y + 1] == 'C' || map.mapArray[x][y + 1] == 'D' || map.mapArray[x][y + 1] == 'E' || map.mapArray[x][y + 1] == 'F')) || (team == team1 && (map.mapArray[x][y + 1] == '1' || map.mapArray[x][y + 1] == '2' || map.mapArray[x][y + 1] == '3' || map.mapArray[x][y + 1] == '4' || map.mapArray[x][y + 1] == '5' || map.mapArray[x][y + 1] == '6')))
		{
			if (team == team2)
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x][y + 1] == teamA[k].name)
					{
						teamA[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
			else if (team == team1)//                     <-------------------------- Inutil?
			{
				for (int k = 0; k < 6; k++)
				{
					if (map.mapArray[x][y + 1] == teamB[k].name)
					{
						teamB[k].hp -= 10;

						for (int i = 0; i < 2; i++)
						{
							map.printMap();
							printPlayersData();
							std::cout << "Remaining Actions: " << currentActions << std::endl;
							std::cout << "Entio: " << teamA[0].name;
							std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

							std::cout << std::endl << std::endl << "Has matado al enemigo " << teamA[k].name << "!";
						}
					}
				}
			}
		}
	}
}

void Player::bowAttack(int x, int y, Player::weapon weapon, Player::attackDirection currentlyAttackDirection, Player::team team)
{
	if (currentlyAttackDirection == UP)
	{
		if (team == team2)
		{
			teamB[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x - i][y] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x - i][y] == teamA[k].name)
						{
							teamA[k].hp -= (11 - i);


							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}
							}
							i = 11;
						}
						else if (map.mapArray[x - i][y] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
		if (team == team1)
		{
			teamA[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x - i][y] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x - i][y] == teamB[k].name)
						{
							teamB[k].hp -= (11 - i);

							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}

							}

							i = 11;
						}
						else if (map.mapArray[x - i][y] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
	}
	if (currentlyAttackDirection == DOWN)
	{
		if (team == team2)
		{
			teamB[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x + i][y] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x + i][y] == teamA[k].name)
						{
							teamA[k].hp -= (11 - i);

							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}
							}
							i = 11;
						}
						else if (map.mapArray[x + i][y] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
		if (team == team1)
		{
			teamA[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x + i][y] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x + i][y] == teamB[k].name)
						{
							teamB[k].hp -= (11 - i);

							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}

							}

							i = 11;
						}
						else if (map.mapArray[x + i][y] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
	}
	if (currentlyAttackDirection == LEFT)
	{
		if (team == team2)
		{
			teamB[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x][y - i] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x][y - i] == teamA[k].name)
						{
							teamA[k].hp -= (11 - i);


							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}
							}
							i = 11;
						}
						else if (map.mapArray[x][y - i] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
		if (team == team1)
		{
			teamA[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x][y - i] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x][y - i] == teamB[k].name)
						{
							teamB[k].hp -= (11 - i);

							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}

							}

							i = 11;
						}
						else if (map.mapArray[x][y - i] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
	}
	if (currentlyAttackDirection == RIGHT)
	{
		teamB[0].arrows--;

		if (team == team2)
		{
			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x][y + i] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x][y + i] == teamA[k].name)
						{
							teamA[k].hp -= (11 - i);


							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}
							}
							i = 11;
						}
						else if (map.mapArray[x][y + i] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
		if (team == team1)
		{
			teamA[0].arrows--;

			for (int i = 0; i <= 10; i++)
			{
				if (i >= 0 && i <= 2)
				{
					if (map.mapArray[x][y + i] == 'X')
					{
						i = 11;
					}
				}
				if (i >= 3)
				{
					for (int k = 0; k < 6; k++)
					{
						if (map.mapArray[x][y + i] == teamB[k].name)
						{
							teamB[k].hp -= (11 - i);

							for (int j = 0; j < 2; j++)
							{

								std::cout << std::endl << std::endl << "-" << (11 - i) << " HP";

								if (teamA[k].hp < 1)
								{
									std::cout << std::endl << std::endl << "Dead";
								}

							}

							i = 11;
						}
						else if (map.mapArray[x][y + i] == 'X')
						{
							i = 11;
						}
					}
				}
			}
		}
	}
	map.printMap();
	printPlayersData();
	std::cout << "Remaining Actions: " << currentActions << std::endl;
	std::cout << "Entio: " << teamA[0].name;
	std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

}

void Player::actionsEntio(enti::InputKey key)
{
	if (currentActions > 0)
	{

		if (currentlyPlayingTeam == team1)
		{

			int x = teamA[0].x, y = teamA[0].y;

			switch (key)
			{
			case enti::InputKey::NONE:
				break;
			case enti::InputKey::w:
				if (map.mapArray[x - 1][y] == 'X' || map.mapArray[x - 1][y] == 'O' || map.mapArray[x - 1][y] == 'A' || map.mapArray[x - 1][y] == 'B' || map.mapArray[x - 1][y] == 'C' || map.mapArray[x - 1][y] == 'D' || map.mapArray[x - 1][y] == 'E' || map.mapArray[x - 1][y] == 'F' || map.mapArray[x - 1][y] == '1' || map.mapArray[x - 1][y] == '2' || map.mapArray[x - 1][y] == '3' || map.mapArray[x - 1][y] == '4' || map.mapArray[x - 1][y] == '5' || map.mapArray[x - 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x - 1][y] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					break;
				}
			case enti::InputKey::W:
				if (map.mapArray[x - 1][y] == 'X' || map.mapArray[x - 1][y] == 'O' || map.mapArray[x - 1][y] == 'A' || map.mapArray[x - 1][y] == 'B' || map.mapArray[x - 1][y] == 'C' || map.mapArray[x - 1][y] == 'D' || map.mapArray[x - 1][y] == 'E' || map.mapArray[x - 1][y] == 'F' || map.mapArray[x - 1][y] == '1' || map.mapArray[x - 1][y] == '2' || map.mapArray[x - 1][y] == '3' || map.mapArray[x - 1][y] == '4' || map.mapArray[x - 1][y] == '5' || map.mapArray[x - 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x - 1][y] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::a:
				if (map.mapArray[x][y - 1] == 'X' || map.mapArray[x][y - 1] == 'O' || map.mapArray[x][y - 1] == 'A' || map.mapArray[x][y - 1] == 'B' || map.mapArray[x][y - 1] == 'C' || map.mapArray[x][y - 1] == 'D' || map.mapArray[x][y - 1] == 'E' || map.mapArray[x][y - 1] == 'F' || map.mapArray[x][y - 1] == '1' || map.mapArray[x][y - 1] == '2' || map.mapArray[x][y - 1] == '3' || map.mapArray[x][y - 1] == '4' || map.mapArray[x][y - 1] == '5' || map.mapArray[x][y - 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);


					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y - 1] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					break;
				}
			case enti::InputKey::A:
				if (map.mapArray[x][y - 1] == 'X' || map.mapArray[x][y - 1] == 'O' || map.mapArray[x][y - 1] == 'A' || map.mapArray[x][y - 1] == 'B' || map.mapArray[x][y - 1] == 'C' || map.mapArray[x][y - 1] == 'D' || map.mapArray[x][y - 1] == 'E' || map.mapArray[x][y - 1] == 'F' || map.mapArray[x][y - 1] == '1' || map.mapArray[x][y - 1] == '2' || map.mapArray[x][y - 1] == '3' || map.mapArray[x][y - 1] == '4' || map.mapArray[x][y - 1] == '5' || map.mapArray[x][y - 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);


					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y - 1] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					break;
				}
			case enti::InputKey::s:
				if (map.mapArray[x + 1][y] == 'X' || map.mapArray[x + 1][y] == 'O' || map.mapArray[x + 1][y] == 'A' || map.mapArray[x + 1][y] == 'B' || map.mapArray[x + 1][y] == 'C' || map.mapArray[x + 1][y] == 'D' || map.mapArray[x + 1][y] == 'E' || map.mapArray[x + 1][y] == 'F' || map.mapArray[x + 1][y] == '1' || map.mapArray[x + 1][y] == '2' || map.mapArray[x + 1][y] == '3' || map.mapArray[x + 1][y] == '4' || map.mapArray[x + 1][y] == '5' || map.mapArray[x + 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);


					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x + 1][y] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::S:
				if (map.mapArray[x + 1][y] == 'X' || map.mapArray[x + 1][y] == 'O' || map.mapArray[x + 1][y] == 'A' || map.mapArray[x + 1][y] == 'B' || map.mapArray[x + 1][y] == 'C' || map.mapArray[x + 1][y] == 'D' || map.mapArray[x + 1][y] == 'E' || map.mapArray[x + 1][y] == 'F' || map.mapArray[x + 1][y] == '1' || map.mapArray[x + 1][y] == '2' || map.mapArray[x + 1][y] == '3' || map.mapArray[x + 1][y] == '4' || map.mapArray[x + 1][y] == '5' || map.mapArray[x + 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);


					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x + 1][y] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::d:
				if (map.mapArray[x][y + 1] == 'X' || map.mapArray[x][y + 1] == 'O' || map.mapArray[x][y + 1] == 'A' || map.mapArray[x][y + 1] == 'B' || map.mapArray[x][y + 1] == 'C' || map.mapArray[x][y + 1] == 'D' || map.mapArray[x][y + 1] == 'E' || map.mapArray[x][y + 1] == 'F' || map.mapArray[x][y + 1] == '1' || map.mapArray[x][y + 1] == '2' || map.mapArray[x][y + 1] == '3' || map.mapArray[x][y + 1] == '4' || map.mapArray[x][y + 1] == '5' || map.mapArray[x][y + 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y + 1] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::D:
				if (map.mapArray[x][y + 1] == 'X' || map.mapArray[x][y + 1] == 'O' || map.mapArray[x][y + 1] == 'A' || map.mapArray[x][y + 1] == 'B' || map.mapArray[x][y + 1] == 'C' || map.mapArray[x][y + 1] == 'D' || map.mapArray[x][y + 1] == 'E' || map.mapArray[x][y + 1] == 'F' || map.mapArray[x][y + 1] == '1' || map.mapArray[x][y + 1] == '2' || map.mapArray[x][y + 1] == '3' || map.mapArray[x][y + 1] == '4' || map.mapArray[x][y + 1] == '5' || map.mapArray[x][y + 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y + 1] = teamA[0].name;
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::z:
			{
				undo();
				break;
			}
			case enti::InputKey::Z:
			{
				undo();
				break;
			}
			case enti::InputKey::x:
			{
				redo();
				break;
			}
			case enti::InputKey::X:
			{
				redo();
				break;
			}
			case enti::InputKey::NUM0:
				break;
			case enti::InputKey::NUM1:
			{
				if (spaceP == true && num1Pressed == false)
				{
					teamA[0].weapon = sword;

					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					std::cout << std::endl;

					std::cout << std::endl << "Select attack direction: " << std::endl;

					std::cout << "   Press 1 = UP " << std::endl;
					std::cout << "   Press 2 = DOWN " << std::endl;
					std::cout << "   Press 3 = LEFT " << std::endl;
					std::cout << "   Press 4 = RIGTH " << std::endl;

					num1Pressed = true;
					num2Pressed = true;
					break;
				}
				else if (num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(UP);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			case enti::InputKey::NUM2:
			{
				if (spaceP == true && num2Pressed == false)
				{
					teamA[0].weapon = bow;

					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					std::cout << std::endl;

					std::cout << std::endl << "Select attack direction: " << std::endl;

					std::cout << "   Press 1 = UP " << std::endl;
					std::cout << "   Press 2 = DOWN " << std::endl;
					std::cout << "   Press 3 = LEFT " << std::endl;
					std::cout << "   Press 4 = RIGTH " << std::endl;
					num2Pressed = true;
					num1Pressed = true;
					break;
				}
				else if (num2Pressed == true)
				{
					map.printMap();
					printPlayersData();

					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(DOWN);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			case enti::InputKey::NUM3:
			{
				if (spaceP == true && num2Pressed == true && num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(LEFT);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			break;
			case enti::InputKey::NUM4:
			{
				if (spaceP == true && num2Pressed == true && num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();

					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(RIGHT);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			break;
			case enti::InputKey::ENTER:
			{
				char i = teamA[0].name;
				orderEntiosByExhausment();
				if (i != teamA[0].name)
				{
					prevEntiosX.clear();
					prevEntiosY.clear();
					currentActions--;
				}
				else
				{
					break;
				}
				map.printMap();
				printPlayersData();
				std::cout << "Remaining Actions: " << currentActions << std::endl;
				std::cout << "Entio: " << teamA[0].name;
				std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
			}
			break;
			case enti::InputKey::SPACEBAR:
			{
				if (spaceP == false)
				{
					std::cout << std::endl << std::endl << "Select a Weapon: " << std::endl;
					std::cout << "   Press 1 = Sword " << std::endl;
					std::cout << "   Press 2 = Bow " << std::endl;
				}
				spaceP = true;
				break;
			}
			case enti::InputKey::ESC:
				break;
			default:
				break;
			}
		}
		else if (currentlyPlayingTeam == team2)
		{

			int x = teamB[0].x, y = teamB[0].y;


			switch (key)
			{
			case enti::InputKey::NONE:
				break;
			case enti::InputKey::w:
				if (map.mapArray[x - 1][y] == 'X' || map.mapArray[x - 1][y] == 'O' || map.mapArray[x - 1][y] == 'A' || map.mapArray[x - 1][y] == 'B' || map.mapArray[x - 1][y] == 'C' || map.mapArray[x - 1][y] == 'D' || map.mapArray[x - 1][y] == 'E' || map.mapArray[x - 1][y] == 'F' || map.mapArray[x - 1][y] == '1' || map.mapArray[x - 1][y] == '2' || map.mapArray[x - 1][y] == '3' || map.mapArray[x - 1][y] == '4' || map.mapArray[x - 1][y] == '5' || map.mapArray[x - 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x - 1][y] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::W:
				if (map.mapArray[x - 1][y] == 'X' || map.mapArray[x - 1][y] == 'O' || map.mapArray[x - 1][y] == 'A' || map.mapArray[x - 1][y] == 'B' || map.mapArray[x - 1][y] == 'C' || map.mapArray[x - 1][y] == 'D' || map.mapArray[x - 1][y] == 'E' || map.mapArray[x - 1][y] == 'F' || map.mapArray[x - 1][y] == '1' || map.mapArray[x - 1][y] == '2' || map.mapArray[x - 1][y] == '3' || map.mapArray[x - 1][y] == '4' || map.mapArray[x - 1][y] == '5' || map.mapArray[x - 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x - 1][y] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::a:
				if (map.mapArray[x][y - 1] == 'X' || map.mapArray[x][y - 1] == 'O' || map.mapArray[x][y - 1] == 'A' || map.mapArray[x][y - 1] == 'B' || map.mapArray[x][y - 1] == 'C' || map.mapArray[x][y - 1] == 'D' || map.mapArray[x][y - 1] == 'E' || map.mapArray[x][y - 1] == 'F' || map.mapArray[x][y - 1] == '1' || map.mapArray[x][y - 1] == '2' || map.mapArray[x][y - 1] == '3' || map.mapArray[x][y - 1] == '4' || map.mapArray[x][y - 1] == '5' || map.mapArray[x][y - 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y - 1] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::A:
				if (map.mapArray[x][y - 1] == 'X' || map.mapArray[x][y - 1] == 'O' || map.mapArray[x][y - 1] == 'A' || map.mapArray[x][y - 1] == 'B' || map.mapArray[x][y - 1] == 'C' || map.mapArray[x][y - 1] == 'D' || map.mapArray[x][y - 1] == 'E' || map.mapArray[x][y - 1] == 'F' || map.mapArray[x][y - 1] == '1' || map.mapArray[x][y - 1] == '2' || map.mapArray[x][y - 1] == '3' || map.mapArray[x][y - 1] == '4' || map.mapArray[x][y - 1] == '5' || map.mapArray[x][y - 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y - 1] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::s:
				if (map.mapArray[x + 1][y] == 'X' || map.mapArray[x + 1][y] == 'O' || map.mapArray[x + 1][y] == 'A' || map.mapArray[x + 1][y] == 'B' || map.mapArray[x + 1][y] == 'C' || map.mapArray[x + 1][y] == 'D' || map.mapArray[x + 1][y] == 'E' || map.mapArray[x + 1][y] == 'F' || map.mapArray[x + 1][y] == '1' || map.mapArray[x + 1][y] == '2' || map.mapArray[x + 1][y] == '3' || map.mapArray[x + 1][y] == '4' || map.mapArray[x + 1][y] == '5' || map.mapArray[x + 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x + 1][y] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::S:
				if (map.mapArray[x + 1][y] == 'X' || map.mapArray[x + 1][y] == 'O' || map.mapArray[x + 1][y] == 'A' || map.mapArray[x + 1][y] == 'B' || map.mapArray[x + 1][y] == 'C' || map.mapArray[x + 1][y] == 'D' || map.mapArray[x + 1][y] == 'E' || map.mapArray[x + 1][y] == 'F' || map.mapArray[x + 1][y] == '1' || map.mapArray[x + 1][y] == '2' || map.mapArray[x + 1][y] == '3' || map.mapArray[x + 1][y] == '4' || map.mapArray[x + 1][y] == '5' || map.mapArray[x + 1][y] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x + 1][y] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::d:
				if (map.mapArray[x][y + 1] == 'X' || map.mapArray[x][y + 1] == 'O' || map.mapArray[x][y + 1] == 'A' || map.mapArray[x][y + 1] == 'B' || map.mapArray[x][y + 1] == 'C' || map.mapArray[x][y + 1] == 'D' || map.mapArray[x][y + 1] == 'E' || map.mapArray[x][y + 1] == 'F' || map.mapArray[x][y + 1] == '1' || map.mapArray[x][y + 1] == '2' || map.mapArray[x][y + 1] == '3' || map.mapArray[x][y + 1] == '4' || map.mapArray[x][y + 1] == '5' || map.mapArray[x][y + 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y + 1] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::D:
				if (map.mapArray[x][y + 1] == 'X' || map.mapArray[x][y + 1] == 'O' || map.mapArray[x][y + 1] == 'A' || map.mapArray[x][y + 1] == 'B' || map.mapArray[x][y + 1] == 'C' || map.mapArray[x][y + 1] == 'D' || map.mapArray[x][y + 1] == 'E' || map.mapArray[x][y + 1] == 'F' || map.mapArray[x][y + 1] == '1' || map.mapArray[x][y + 1] == '2' || map.mapArray[x][y + 1] == '3' || map.mapArray[x][y + 1] == '4' || map.mapArray[x][y + 1] == '5' || map.mapArray[x][y + 1] == '6')
				{
					break;
				}
				else
				{
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					prevEntiosX.push_back(x);
					prevEntiosY.push_back(y);

					map.mapArray[x][y] = map.defaultMap[x][y];
					map.mapArray[x][y + 1] = teamB[0].name;
					teamB[0].turnExhausment++;
					teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
					findEntioPosition();
					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamB[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					break;
				}
			case enti::InputKey::z:
			{
				undo();
				break;
			}
			case enti::InputKey::Z:
			{
				undo();
				break;
			}
			case enti::InputKey::x:
			{
				redo();
				break;
			}
			case enti::InputKey::X:
			{
				redo();
				break;
			}
			case enti::InputKey::NUM0:
				break;
			case enti::InputKey::NUM1:
			{
				if (spaceP == true && num1Pressed == false)
				{
					teamB[0].weapon = sword;

					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					std::cout << std::endl;

					std::cout << std::endl << "Select attack direction: " << std::endl;

					std::cout << "   Press 1 = UP " << std::endl;
					std::cout << "   Press 2 = DOWN " << std::endl;
					std::cout << "   Press 3 = LEFT " << std::endl;
					std::cout << "   Press 4 = RIGTH " << std::endl;

					num1Pressed = true;
					num2Pressed = true;
					break;
				}
				else if (num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(UP);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;

					std::cout << std::endl << "Ataque hacia arriba" << std::endl;


					break;
				}
			}
			case enti::InputKey::NUM2:
			{
				if (spaceP == true && num2Pressed == false)
				{
					teamB[0].weapon = bow;

					map.printMap();
					printPlayersData();
					currentActions--;
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
					std::cout << std::endl;


					std::cout << std::endl << "Select attack direction: " << std::endl;

					std::cout << "   Press 1 = UP " << std::endl;
					std::cout << "   Press 2 = DOWN " << std::endl;
					std::cout << "   Press 3 = LEFT " << std::endl;
					std::cout << "   Press 4 = RIGTH " << std::endl;
					num2Pressed = true;
					num1Pressed = true;

					std::cout << std::endl << "Arco" << std::endl;

					break;
				}
				else if (num2Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(DOWN);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			case enti::InputKey::NUM3:
			{
				if (spaceP == true && num2Pressed == true && num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(LEFT);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			break;
			case enti::InputKey::NUM4:
			{
				if (spaceP == true && num2Pressed == true && num1Pressed == true)
				{
					teamA[0].turnExhausment++;
					teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
					currentActions--;
					map.printMap();
					printPlayersData();
					std::cout << "Remaining Actions: " << currentActions << std::endl;
					std::cout << "Entio: " << teamA[0].name;
					std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

					std::cout << std::endl << std::endl << "There's no enemy above, you failled. " << std::endl;
					attack(RIGHT);
					num1Pressed = false;
					num2Pressed = false;
					spaceP = false;
					break;
				}
			}
			case enti::InputKey::ENTER:
			{
				char i = teamB[0].name;
				orderEntiosByExhausment();
				if (i != teamB[0].name)
				{
					prevEntiosX.clear();
					prevEntiosY.clear();
					currentActions--;
				}
				else
				{
					break;
				}
				map.printMap();
				printPlayersData();
				std::cout << "Remaining Actions: " << currentActions << std::endl;
				std::cout << "Entio: " << teamB[0].name;
				std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
			}
			break;
			case enti::InputKey::SPACEBAR:
			{
				if (spaceP == false)
				{
					std::cout << std::endl << std::endl << "Select a Weapon: " << std::endl;
					std::cout << "   Press 1 = Sword " << std::endl;
					std::cout << "   Press 2 = Bow " << std::endl;
				}
				spaceP = true;
				break;
			}
			case enti::InputKey::ESC:
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (printed == false)
		{
			std::cout << std::endl << "Press ENTER to finish your turn.";
		}
		printed = true;

		if (key == enti::InputKey::ENTER)
		{
			turnManager();
			map.printMap();
			printPlayersData();
			std::cout << "Remaining Actions: " << currentActions << std::endl;
			if (currentlyPlayingTeam == team1)
			{
				std::cout << "Entio: " << teamA[0].name;
			}
			if (currentlyPlayingTeam == team2)
			{
				std::cout << "Entio: " << teamA[0].name;
			}
			std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;
			printed = false;
		}
	}

}

void Player::undo()
{
	if (currentlyPlayingTeam == team1)
	{
		if (prevEntiosX.size() > 0)
		{
			nextEntiosX.push_back(teamA[0].x);
			nextEntiosY.push_back(teamA[0].y);

			teamA[0].turnExhausment--;
			teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
			currentActions++;
			map.mapArray[teamA[0].x][teamA[0].y] = map.defaultMap[teamA[0].x][teamA[0].y];
			teamA[0].x = prevEntiosX[prevEntiosX.size() - 1];
			teamA[0].y = prevEntiosY[prevEntiosX.size() - 1];
			map.mapArray[teamA[0].x][teamA[0].y] = teamA[0].name;
			map.printMap();
			printPlayersData();
			std::cout << "Remaining Actions: " << currentActions << std::endl;
			std::cout << "Entio: " << teamA[0].name;
			std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

			prevEntiosX.pop_back();
			prevEntiosY.pop_back();
		}
	}
	if (currentlyPlayingTeam == team2)
	{
		if (prevEntiosX.size() > 0)
		{
			nextEntiosX.push_back(teamB[0].x);
			nextEntiosY.push_back(teamB[0].y);

			teamB[0].turnExhausment--;
			teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
			currentActions++;
			map.mapArray[teamB[0].x][teamB[0].y] = map.defaultMap[teamB[0].x][teamB[0].y];
			teamB[0].x = prevEntiosX[prevEntiosX.size() - 1];
			teamB[0].y = prevEntiosY[prevEntiosY.size() - 1];
			map.mapArray[teamB[0].x][teamB[0].y] = teamB[0].name;
			map.printMap();
			printPlayersData();
			std::cout << "Remaining Actions: " << currentActions << std::endl;
			std::cout << "Entio: " << teamB[0].name;
			std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;

			prevEntiosX.pop_back();
			prevEntiosY.pop_back();
		}
	}
}

void Player::redo()
{
	if (currentlyPlayingTeam == team1)
	{
		if (nextEntiosX.size() > 0)
		{
			prevEntiosX.push_back(teamA[0].x);
			prevEntiosY.push_back(teamA[0].y);

			teamA[0].turnExhausment++;
			teamA[0].exhausment = teamA[0].turnExhausment + teamA[0].matchExhausment;
			currentActions--;
			map.mapArray[teamA[0].x][teamA[0].y] = map.defaultMap[teamA[0].x][teamA[0].y];
			teamA[0].x = nextEntiosX[nextEntiosX.size() - 1];
			teamA[0].y = nextEntiosY[nextEntiosY.size() - 1];

			map.mapArray[teamA[0].x][teamA[0].y] = teamA[0].name;
			map.printMap();
			printPlayersData();
			std::cout << "Remaining Actions: " << currentActions << std::endl;
			std::cout << "Entio: " << teamA[0].name;
			std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;


			nextEntiosX.pop_back();
			nextEntiosY.pop_back();
		}
	}
	if (currentlyPlayingTeam == team2)
	{
		if (nextEntiosX.size() > 0)
		{
			prevEntiosX.push_back(teamB[0].x);
			prevEntiosY.push_back(teamB[0].y);

			teamB[0].turnExhausment++;
			teamB[0].exhausment = teamB[0].turnExhausment + teamB[0].matchExhausment;
			currentActions--;
			map.mapArray[teamB[0].x][teamB[0].y] = map.defaultMap[teamB[0].x][teamB[0].y];
			teamB[0].x = nextEntiosX[nextEntiosX.size() - 1];
			teamB[0].y = nextEntiosY[nextEntiosY.size() - 1];

			map.mapArray[teamB[0].x][teamB[0].y] = teamB[0].name;
			map.printMap();
			printPlayersData();
			std::cout << "Remaining Actions: " << currentActions << std::endl;
			std::cout << "Entio: " << teamB[0].name;
			std::cout << "\n" << "Team playing: " << currentlyPlayingTeam;


			nextEntiosX.pop_back();
			nextEntiosY.pop_back();
		}
	}
}

int Player::endGame()
{
	int j = 0, k = 0;

	for (int i = 0; i < 6; i++)
	{
		if (teamA[i].hp < 1)
		{
			j++;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (teamA[i].hp < 1)
		{
			k++;
		}
	}
	if (j == 6)
	{
		return 1;
	}
	if (k == 6)
	{
		return 2;
	}
	else
	{
		return 0;
	}

}

Player::~Player()
{

}
