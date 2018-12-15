/*
	2018.10.05 Kwon ki seok
	TextureManager.h
	텍스쳐 로드 매니저 구성
*/
#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);

	static SDL_Texture* LoadMapTexture(const char* fileName);
	static void MapDraw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};