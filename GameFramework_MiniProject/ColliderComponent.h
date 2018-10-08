/*
	2018.10.09 Kwon ki seok
	ColliderComponent.h

	�浹 ������ ���� ������Ʈ ����

*/

#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		//��ƼƼ�� TransformComponent�� ���� ��� �߰�����
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	
		Game::colliders.push_back(this);
	}

	void update() override
	{
		//x, y ����ȯ
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};