/*
	2018.10.05 Kwon ki seok
	ECS.h
	Entity Component System 엔티티 구성 요소 시스템

	아키텍처 패턴. 게임 장면의 모든 객체가 엔티티(ex. 적, 총알, 차량 등)인 엔티티를 정의할 때
	더 큰 유연성을 허용하는 상속 원칙보다 컴포지션을 따름.
	Unity엔진이 ECS를 통해 오브젝트 중심->데이터 중심의 디자인으로 접근함

	Entitiy = 유니티의 Empty GameObject와 유사함. 기본적으론 아무 기능 없고 Component를 갖고있음
	Component = 유니티의 Component는 Data + Behavior / ECS에서는 Data뿐
	
	ECS의 장점은 각자 역할만을 담당하기에 재사용성이 뛰어나고 숙지하고 있다면 유지보수가 쉬움
	단점은 데이터 기반의 구조이므로 OOP에 적응되어있다면 난해하다

	[참고링크]
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
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

//inline 함수. 호출 부분을 함수 코드로 치환함
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

//template 클래스 혹은 함수의 객체 타입에 대해 따로 고려하지 않고 작성가능
//noexcept 키워드. 이 함수가 예외를 방출하지 않을 것임을 명시
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
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


//unique_ptr
//C++에서 제공하는 스마트 포인터 <memory>헤더 인클루드 시 사용가능
//동적으로 힙 영역에 할당된 인스턴스에 대한 소유권을 얻어 객체가 사라질 경우 해당 인스턴스를 해제
//[참고링크] http://bunhere.tistory.com/407
class Entity
{
private:
	Manager & manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	void update()
	{
		for (auto& c : components) c->update();		
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
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
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

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
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};