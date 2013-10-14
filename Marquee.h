#pragma once
#include <tString.h>
#include <SpriteIrrAdapter.h>
#include <LerpAnimation.h>
#include <array>

class Marquee{
public:
	Marquee(int priority);
	void draw();
private:
	int m_Y;
	int m_V;
	int m_XLeft;
	int m_XRight;
	std::array<Sprite, 2> m_Image;
	LerpAnimation m_Animation;
};