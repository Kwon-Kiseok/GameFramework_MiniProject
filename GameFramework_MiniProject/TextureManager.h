/*
	2018.10.05 Kwon ki seok
	TextureManager.h
	�ؽ��� �ε� �Ŵ��� ����
*/
#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};