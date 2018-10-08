/*
	2018.10.09 Kwon ki seok
	Vector2D.h
	
	2D연산에 사용될 사칙연산 기능들을 
	Vector2D 클래스로 지정 후 기본 사칙연산 연산자와
	복합대입연산자를 정의해줌
*/

#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply (const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	//사칙연산 연산자 정의
	//friend를 통해 접근 지정자를 무시한다
	//OOP 개념에 위배되지만 연산자 오버로딩의 경우 예외적으로 필요함
	//[참고 링크]http://genesis8.tistory.com/98 http://thrillfighter.tistory.com/283
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	//복합대입연산자 정의
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};