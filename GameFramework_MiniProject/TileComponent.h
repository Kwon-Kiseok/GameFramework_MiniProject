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
	Vector2D position;

	TileComponent() = default;

	~TileComponent() { SDL_DestroyTexture(texture); }

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
	{
		texture = TextureManager::LoadTexture(path);
		
		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};