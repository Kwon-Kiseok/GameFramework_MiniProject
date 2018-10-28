#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"
//extern 으로 ECS 안에 있던 Manager 전역 클래스 사용
extern Manager manager;

Map::Map(std::string tID, int mScale, int tSize) 
	: texID(tID) , mapScale(mScale) , tileSize(tSize)
{
	scaledSize = mScale * tSize;
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
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;

			//반복을 돌며 해당 타일타입의 타일들을 위치마다 넣어주고 있다.
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x*scaledSize, y*scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}
