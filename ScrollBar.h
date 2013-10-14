#pragma once
#include <tString.h>
#include <SpriteIrrAdapter.h>
#include <LerpAnimation.h>

class ScrollBar{
public:
	ScrollBar(int priority);
	void draw();
	void setPosition(double percent);
private:
	double currentPos_percent;
	LerpAnimation lerp;
	Sprite bar;
	Sprite button;
};