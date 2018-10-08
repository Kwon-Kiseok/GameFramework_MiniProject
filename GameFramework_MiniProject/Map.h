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

	Map();
	~Map();

	static void LoadMap(std::string path, int sizeX, int sizeY);
	
private:


};