/*
2018.10.24 Kwon ki seok
Animation.h

�ִϸ��̼� ���� ��ü�� ���� ����ü

*/

#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {}
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};