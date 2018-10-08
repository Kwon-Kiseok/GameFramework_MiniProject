/*
	2018.10.09 Kwon ki seok
	Collision.h

	충돌체크를 위한 AABB 검사 선언

	[AABB 충돌 개념 참고 링크]
	https://blog.naver.com/o2kim0225/20201248088
*/
#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};