/*
	2018.10.28 Kwon ki seok
	AssetManager.h

	�ּ� ���� ���ոŴ���
	������Ʈ�� �����ϰų� �ؽ��� ��θ� �޾ƿ� id �� ������ش�
*/

#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();

	//���ӿ�����Ʈ ����
	void CreateProjectile(Vector2D pos,Vector2D vel, int range, int speed, std::string id);


	//�ؽ��� ����
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:

	Manager * manager;
	std::map<std::string, SDL_Texture*> textures;

};