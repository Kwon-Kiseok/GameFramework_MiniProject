/*
	2018.10.09 Kwon ki seok
	KeyboardController.h

	키보드 입력 정보를 처리하는 컨트롤러 구성

	2018.10.24 Kwon ki seok
	+ 키 입력마다 애니메이션 제어 추가해줌
*/

#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent * transform;
	SpriteComponent *sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		//SDL_KEYDOWN 과 SDLK 를 통한
		//키가 눌렸을 때의 이벤트 처리
		//velocity 값을 제어해줌으로 TransformComponent.h 에서 지정해준
		//position 값을 변동시켜 줌
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				transform->velocity.y = +1;
				sprite->Play("Walk");
				break;
			case SDLK_d:
				transform->velocity.x = +1;
				sprite->Play("Walk");
				break;

				default:
					break;
			}
		}

		//SDL_KEYUP 과 SDLK 를 통한
		//키 입력 중단 되었을 때 이벤트 처리
		//velocity 값을 0으로 돌려 키 입력이 중단 되었을 경우 움직이지 않도록 함
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;

			default:
				break;
			}
		}

	}
};