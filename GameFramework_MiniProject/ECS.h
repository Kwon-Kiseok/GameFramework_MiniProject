/*
	2018.10.05 Kwon ki seok
	ECS.h
	Entity Component System ��ƼƼ ���� ��� �ý���

	��Ű��ó ����. ���� ����� ��� ��ü�� ��ƼƼ(ex. ��, �Ѿ�, ���� ��)�� ��ƼƼ�� ������ ��
	�� ū �������� ����ϴ� ��� ��Ģ���� ���������� ����.
	Unity������ ECS�� ���� ������Ʈ �߽�->������ �߽��� ���������� ������

	Entitiy = ����Ƽ�� Empty GameObject�� ������. �⺻������ �ƹ� ��� ���� Component�� ��������
	Component = ����Ƽ�� Component�� Data + Behavior / ECS������ Data��
	
	ECS�� ������ ���� ���Ҹ��� ����ϱ⿡ ���뼺�� �پ�� �����ϰ� �ִٸ� ���������� ����
	������ ������ ����� �����̹Ƿ� OOP�� �����Ǿ��ִٸ� �����ϴ�

	[����ũ]
	https://m.blog.naver.com/dlwhdgur20/221012364253
	https://www.youtube.com/watch?v=XsvI8Sng6dk&index=9&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
*/
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;


//inline �Լ�. ȣ�� �κ��� �Լ� �ڵ�� ġȯ��
inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

//template Ŭ���� Ȥ�� �Լ��� ��ü Ÿ�Կ� ���� ���� ������� �ʰ� �ۼ�����
//noexcept Ű����. �� �Լ��� ���ܸ� �������� ���� ������ ���
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity * entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
private:
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void update()
	{
		for (auto& c : components) c->update();
		for (auto& c : components) c->draw();
	}
	void draw() {}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArags)
	{
		T* c(new T(std::forward<TArgs>(mArags)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}


};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};