#pragma once
#pragma once
#include <array>
#include <deque>
#include <vector>
#include <functional>

#include <tString.h>
#include <RingIndex.h>
#include <LerpAnimation.h>

#include <SpriteIrrAdapter.h>
#include "GameList.h"

class IScene;

class Level2Menu{
public:
	enum{
		Delay = 3,
		NumOfTitles = 13 // äÔêîå¿íË
	};

	Level2Menu();
	void addItem(GameData gameData);

	void next();
	void prev();

	void draw();
	std::shared_ptr<IScene> select();
private:
	std::vector<GameData> m_GameList;
	
	std::deque<Sprite> m_Titles;
	std::array<Sprite, NumOfTitles> m_Backgrounds;
	Sprite m_Select;

	TUL::RingIndex m_CurrentIndex;
	LerpAnimation lerp;
};