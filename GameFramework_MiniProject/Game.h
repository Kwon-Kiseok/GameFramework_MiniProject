/*
	2018.10.05 Kwon ki seok
	Game.h
	게임 클래스 구성
*/
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game {

public:
	Game();
	~Game();
	
	void init(const char* title, int width, int height, bool fullscreen);
	
	void GameClear();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	int cnt = 0;
	SDL_Window *window;
	SDL_Window *mapWindow;
	SDL_Window *ClearWindow;
	SDL_Renderer *mapRenderer;
	SDL_Renderer *ClearRenderer;
	SDL_Texture *ClearTex;
	SDL_Texture *mapWinTex;
};