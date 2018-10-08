/*
	2018.10.09 Kwon ki seok
	Collision.h

	�浹üũ�� ���� AABB �˻� ����

	[AABB �浹 ���� ���� ��ũ]
	https://blog.naver.com/o2kim0225/20201248088
*/
#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};