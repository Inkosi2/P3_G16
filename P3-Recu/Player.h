#pragma once
#include "Map.h"
#include "Input.hh"
#include <vector>

const int maxActions = 10;
const int maxHp = 10;
const int startingExhausment = 0;
const int maxArrows = 10;

class Player
{
public:

	Map map;

	std::string nameList1[6] = {"Hannibal", "Murdock", "Faceman", "M.A. Baracus", "MacGyver", "Chuck"};
	std::string nameList2[6] = {"Albert", "Jordi", "Rita", "Freddie", "Hector", "Oriol"};

	enti::InputKey lastKey = enti::InputKey::NONE;

	bool printed = false;
	bool spaceP = false, num1Pressed = false, num2Pressed = false;

	enum team { team1, team2 };
	enum weapon { sword, bow, none };
	enum attackDirection { UP, DOWN, LEFT, RIGHT, NONE };

	struct entio
	{
		char name;
		int exhausment;
		int matchExhausment;
		int turnExhausment;
		int x;
		int y;
		int hp;
		weapon weapon;
		int arrows = maxArrows;
		team team;
	};



	int currentActions;
	entio teamA[6];
	entio teamB[6];
	team currentlyPlayingTeam;
	entio currentlyPlayingEntio;

	std::vector<int>prevEntiosX;
	std::vector<int>prevEntiosY;
	std::vector<int>nextEntiosX;
	std::vector<int>nextEntiosY;


	Player();
	void setPlayersData(Map map);
	void findEntioPosition();
	void orderEntiosByExhausment();
	void printPlayersData();
	void turnManager();
	void attack(attackDirection currentlyAttackDirection);
	void swordAttack(int x, int y, Player::weapon weapon, Player::attackDirection currentlyAttackDirection, team team);
	void bowAttack(int x, int y, Player::weapon weapon, Player::attackDirection currentlyAttackDirection, team team);
	void actionsEntio(enti::InputKey key);
	void undo();
	void redo();
	int endGame();
	~Player();
};
