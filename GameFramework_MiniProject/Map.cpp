#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map()
{
	
}

Map::~Map()
{
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;	//맵 소스의 x와 y 크기값

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			//mapFile 안의 문자열 숫자들을 읽어들어와서 atoi를 통해 문자 스트링을 정수로 변환

			mapFile.get(c);
			srcY = atoi(&c) * 32;
			mapFile.get(c);
			srcX = atoi(&c) * 32;

			//반복을 돌며 해당 타일타입의 타일들을 위치마다 넣어주고 있다.
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}


