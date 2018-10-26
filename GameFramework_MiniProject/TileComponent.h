/*
	2018.10.09 Kwon ki seok
	TileComponent.h

	원하는 크기의 타일 맵을 생성할 수 있도록 구성
	tileID와 path를 통해 생성 구문 간결화
*/

#pragma once

#include "ECS.h"
#include <SDL.h>

class TileComponent : public Component
{
public:

	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;

	~TileComponent() { SDL_DestroyTexture(texture); }

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};