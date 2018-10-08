/*
	2018.10.09 Kwon ki seok
	ColliderComponent.h

	충돌 감지를 위한 컴포넌트 구성

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
		//엔티티에 TransformComponent가 없을 경우 추가해줌
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	
		Game::colliders.push_back(this);
	}

	void update() override
	{
		//x, y 형변환
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};