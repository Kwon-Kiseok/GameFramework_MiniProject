/*
	2018.10.05 Kwon ki seok
	GameObject.h
	���� ������Ʈ Ŭ����
*/
#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* tecturesheet, SDL_Renderer* ren, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};