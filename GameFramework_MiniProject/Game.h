/*
	2018.10.05 Kwon ki seok
	Game.h
	게임 클래스 구성
*/
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game {

public:
	Game();
	~Game();
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	bool running() { return isRunning; }

private:
	int cnt = 0;
	bool isRunning = false;
	SDL_Window *window;
};