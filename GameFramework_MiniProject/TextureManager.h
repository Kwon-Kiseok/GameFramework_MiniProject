/*
	2018.10.05 Kwon ki seok
	TextureManager.h
	텍스쳐 로드 매니저 구성
*/
#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};