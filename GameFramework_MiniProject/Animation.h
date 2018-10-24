/*
2018.10.24 Kwon ki seok
Animation.h

애니메이션 생성 객체를 위한 구조체

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