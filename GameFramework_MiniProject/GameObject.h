/*
	2018.10.05 Kwon ki seok
	GameObject.h
	게임 오브젝트 클래스
*/
#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* tecturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;


};