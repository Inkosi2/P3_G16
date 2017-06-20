#pragma once

const int heightMap = 36, widthMap = 73;


class Map
{
public:

	char mapArray[heightMap][widthMap];
	char defaultMap[heightMap][widthMap];

	Map();
	void printMap();
	void printStartingMap();
	~Map();
};

