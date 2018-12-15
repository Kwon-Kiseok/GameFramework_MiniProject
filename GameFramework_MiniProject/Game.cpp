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

//Entitiy를 생성해 줌 Unity에서 빈 오브젝트 생성하는 거와 동일
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
			std::cout << "길을 잘못들어서 미로에 갇히게 되었다" << std::endl;
			std::cout << "내게 있는건 흙 묻고 젖은 알아보기 힘든 지도 뿐이다" << std::endl;
			std::cout << "빨리 출구를 찾아내서 나가도록 하자" << std::endl;
			std::cout << "---------------조작키---------------" << std::endl;
			std::cout << "WASD - 캐릭터 이동" << std::endl;
			std::cout << "ESC - 게임 종료" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		//멀티 윈도우 기능을 이용한 맵 보여주는 윈도우
		mapWindow = SDL_CreateWindow("HINT", 200, 200, 300, 300, flags);
		mapRenderer = SDL_CreateRenderer(mapWindow, -1, 0);		
		mapWinTex = IMG_LoadTexture(mapRenderer, "assets/map.png");

		isRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//애셋 메니저를 통한 텍스쳐 ID 등록
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/Player_anim.png");

	//애셋 매니저를 통한 폰트 등록
	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);

	//ECS implementation

	map->LoadMap("assets/map.map", 25, 20);

	//player 에게 할당해주는 컴포넌트들
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

//생성 객체들 그룹화 
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

	//sstream 을 통해 stringstream을 만들어서 
	//ss에 Player Position 문구에 playerPos 값을 string으로 변환해서 붙인다
	//그 후 SetLabel에 ss를 통째로 넣어준다.
	//업데이트로 플레이어의 포지션값을 실시간으로 보여준다.
	std::stringstream ss;
	ss << "Current coordinates: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

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


	//카메라 위치 플레이어 따라다니며 고정
	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 200);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 200);
	

	//카메라 경계면 바운딩 처리
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
		std::cout << "야호! 탈출이다!" << std::endl;
		std::cout << "무사히 탈출하셨습니다" << std::endl;
		std::cout << "축하합니다!" << std::endl;

		clean();
	}
}