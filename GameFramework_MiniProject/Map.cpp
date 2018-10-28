#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"
//extern ���� ECS �ȿ� �ִ� Manager ���� Ŭ���� ���
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

	int srcX, srcY;	//�� �ҽ��� x�� y ũ�Ⱚ

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			//mapFile ���� ���ڿ� ���ڵ��� �о���ͼ� atoi�� ���� ���� ��Ʈ���� ������ ��ȯ

			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;

			//�ݺ��� ���� �ش� Ÿ��Ÿ���� Ÿ�ϵ��� ��ġ���� �־��ְ� �ִ�.
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
