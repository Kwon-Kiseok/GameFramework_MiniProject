/*
	2018.10.09 Kwon ki seok
	Vector2D.h
	
	2D���꿡 ���� ��Ģ���� ��ɵ��� 
	Vector2D Ŭ������ ���� �� �⺻ ��Ģ���� �����ڿ�
	���մ��Կ����ڸ� ��������
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

	//��Ģ���� ������ ����
	//friend�� ���� ���� �����ڸ� �����Ѵ�
	//OOP ���信 ��������� ������ �����ε��� ��� ���������� �ʿ���
	//[���� ��ũ]http://genesis8.tistory.com/98 http://thrillfighter.tistory.com/283
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	//���մ��Կ����� ����
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};