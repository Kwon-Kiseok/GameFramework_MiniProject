/*
	2018.10.05 Kwon ki seok
	Game.cpp
*/
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map *map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

//Entitiy를 생성해 줌 Unity에서 빈 오브젝트 생성하는 거와 동일
auto& player(manager.addEntity());


Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	//애셋 메니저를 통한 텍스쳐 ID 등록
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/Player_anim.png");
	assets->AddTexture("projectile", "assets/proj.png");

	map = new Map("terrain", 3, 32);

	//ECS implementation

	map->LoadMap("assets/map.map", 25, 20);

	//player 에게 할당해주는 컴포넌트들
	player.addComponent<TransformComponent>(800.0f,600.0f,32,32,2);
	player.addComponent<SpriteComponent>("player",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//총알 생성
	assets->CreateProjectile(Vector2D(600, 600),Vector2D(2,0) ,200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");

}

//생성 객체들 그룹화 
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();
	

	//충돌처리 구문
	for (auto&c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto&p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "플레이어 충돌" << std::endl;
			//플레이어와 총알의 충돌 시 총알 파괴
			p->destroy();
		}
	}


	//카메라 위치 플레이어 따라다니며 고정
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;
	

	//카메라 경계면 바운딩 처리
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}


void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	/*for (auto& c : colliders)
	{
		c->draw();
	}*/

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
