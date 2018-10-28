/*
	2018.10.28 Kwon ki seok
	ProjectileComponent.h 

	총알 오브젝트 생성 및 외부로 나갈 때 파괴 처리하는 컴포넌트 
*/

#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp , Vector2D vel) : range(rng) , speed(sp), velocity(vel) {}
	~ProjectileComponent() {}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "사정거리 밖" << std::endl;
			entity->destroy();
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w
				|| transform->position.x < Game::camera.x 
				|| transform->position.y > Game::camera.y + Game::camera.h
				|| transform->position.y < Game::camera.y)
		{
			std::cout << "바운드 밖" << std::endl;
			entity->destroy();
		}
	}

private:

	TransformComponent * transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};