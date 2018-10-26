/*
	2018.10.05 Kwon ki seok
	Map.h
	맵 클래스 구성
*/
#pragma once
#include <string>

class Map 
{
public:

	Map(const char* mfilePath, int mScale, int tSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};