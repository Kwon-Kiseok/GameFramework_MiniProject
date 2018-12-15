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
#include <sstream>
#include <SDL_mixer.h>

Mix_Music* BGM = NULL;

Map *map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,0,520 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

//Entitiy�� ������ �� Unity���� �� ������Ʈ �����ϴ� �ſ� ����
auto& player(manager.addEntity());
auto& label(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
		{
			std::cout << "���� �߸��� �̷ο� ������ �Ǿ���" << std::endl;
			std::cout << "���� �ִ°� �� ���� ���� �˾ƺ��� ���� ���� ���̴�" << std::endl;
			std::cout << "���� �ⱸ�� ã�Ƴ��� �������� ����" << std::endl;
			std::cout << "---------------����Ű---------------" << std::endl;
			std::cout << "WASD - ĳ���� �̵�" << std::endl;
			std::cout << "ESC - ���� ����" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		//��Ƽ ������ ����� �̿��� �� �����ִ� ������
		mapWindow = SDL_CreateWindow("HINT", 200, 200, 300, 300, flags);
		mapRenderer = SDL_CreateRenderer(mapWindow, -1, 0);		
		mapWinTex = IMG_LoadTexture(mapRenderer, "assets/map.png");

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//�ּ� �޴����� ���� �ؽ��� ID ���
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/Player_anim.png");

	//�ּ� �Ŵ����� ���� ��Ʈ ���
	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);

	//ECS implementation

	map->LoadMap("assets/map.map", 25, 20);

	//player ���� �Ҵ����ִ� ������Ʈ��
	player.addComponent<TransformComponent>(0.0f,1350.0f,32,32,2);
	player.addComponent<SpriteComponent>("player",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_VolumeMusic(18);
	BGM = Mix_LoadMUS("assets/Town_BGM.mp3");
	Mix_PlayMusic(BGM, -1);

}

//���� ��ü�� �׷�ȭ 
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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

	//sstream �� ���� stringstream�� ���� 
	//ss�� Player Position ������ playerPos ���� string���� ��ȯ�ؼ� ���δ�
	//�� �� SetLabel�� ss�� ��°�� �־��ش�.
	//������Ʈ�� �÷��̾��� �����ǰ��� �ǽð����� �����ش�.
	std::stringstream ss;
	ss << "Current coordinates: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	manager.refresh();
	manager.update();
	

	//�浹ó�� ����
	for (auto&c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}


	//ī�޶� ��ġ �÷��̾� ����ٴϸ� ����
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 200);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 200);
	

	//ī�޶� ���� �ٿ�� ó��
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;

	GameClear();
}


void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderClear(mapRenderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	SDL_RenderCopy(mapRenderer, mapWinTex, NULL, NULL);
	label.draw();
	SDL_RenderPresent(mapRenderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	Mix_FreeMusic(BGM);
	Mix_CloseAudio();
	SDL_DestroyTexture(mapWinTex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mapWindow);
	SDL_DestroyRenderer(mapRenderer);
	SDL_Quit();
}

void Game::GameClear()
{
	if (player.getComponent<TransformComponent>().position.x >= 1919 &&
		player.getComponent<TransformComponent>().position.x <= 1952 &&
		player.getComponent<TransformComponent>().position.y >= -54 &&
		player.getComponent<TransformComponent>().position.y <= 33)
	{
		std::cout << "��ȣ! Ż���̴�!" << std::endl;
		std::cout << "������ Ż���ϼ̽��ϴ�" << std::endl;
		std::cout << "�����մϴ�!" << std::endl;

		clean();
	}
}