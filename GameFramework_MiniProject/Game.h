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

class ColliderComponent;

class Game {

public:
	Game();
	~Game();
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	static void AddTile(int srcX,int srcY ,int xpos, int ypos);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
	bool running() { return isRunning; }

private:
	int cnt = 0;
	SDL_Window *window;
};