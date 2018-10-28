/*
	2018.10.28 Kwon ki seok
	AssetManager.h

	애셋 관리 통합매니저
	오브젝트를 생성하거나 텍스쳐 경로를 받아와 id 에 등록해준다
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

	//게임오브젝트 관리
	void CreateProjectile(Vector2D pos,Vector2D vel, int range, int speed, std::string id);


	//텍스쳐 관리
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:

	Manager * manager;
	std::map<std::string, SDL_Texture*> textures;

};