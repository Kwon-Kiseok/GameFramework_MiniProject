/*
	2018.10.09 Kwon ki seok
	KeyboardController.h

	Ű���� �Է� ������ ó���ϴ� ��Ʈ�ѷ� ����
*/

#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent * transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		//SDL_KEYDOWN �� SDLK �� ����
		//Ű�� ������ ���� �̺�Ʈ ó��
		//velocity ���� ������������ TransformComponent.h ���� ��������
		//position ���� �������� ��
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_s:
				transform->velocity.y = +1;
				break;
			case SDLK_d:
				transform->velocity.x = +1;
				break;

				default:
					break;
			}
		}

		//SDL_KEYUP �� SDLK �� ����
		//Ű �Է� �ߴ� �Ǿ��� �� �̺�Ʈ ó��
		//velocity ���� 0���� ���� Ű �Է��� �ߴ� �Ǿ��� ��� �������� �ʵ��� ��
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;

			default:
				break;
			}
		}

	}
};