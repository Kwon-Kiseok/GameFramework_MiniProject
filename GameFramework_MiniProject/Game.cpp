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

Map *map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;

//Entitiy를 생성해 줌 Unity에서 빈 오브젝트 생성하는 거와 동일
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "assets/terrain_ss.png"; // 맵파일 로드

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

	map = new Map();

	//ECS implementation

	Map::LoadMap("assets/map.map", 25, 20);

	//player 에게 할당해주는 컴포넌트들
	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("assets/Player_anim.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	
}

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
	manager.refresh();
	manager.update();
	
	//플레이어의 벡터 방향값과 이동속도값을 변수로 저장  
	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;


	//그려지는 타일 좌표값들을 플레이어가 이동하는 것에 반대만큼 똑같이 주어 
	//반복적으로 그려지면서 맵 스크롤링을 구현
	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}
}


void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& t : players)
	{
		t->draw();
	}

	for (auto & t : enemies)
	{
		t->draw();
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

void Game::AddTile(int srcX,int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}