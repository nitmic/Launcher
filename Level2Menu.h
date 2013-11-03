#pragma once
#pragma once
#include <array>
#include <deque>
#include <vector>
#include <functional>

#include <tString.hpp>
#include <RingIndex.h>
#include <LerpAnimation.h>

#include <SpriteIrrAdapter.h>

#include "ScrollBar.h"
#include "GameList.h"

#include <MovieIrrAdapter.h>
#include <Delay.h>

class IScene;

class Level2Menu{
public:
	Level2Menu(int priority);
	void addItem(GameData gameData);

	void next();
	void prev();

	void draw();
	TUL::tString select();
	void step();
private:
	void addSelectItemUpdate();
	std::vector<GameData> m_GameList;
	
	std::deque<Sprite> m_Titles;
	std::array<Sprite, config::menu::NumOfMenuItems> m_Backgrounds;
	Sprite m_Select;

	ScrollBar m_Bar;

	int m_Priority;
	TUL::RingIndex m_CurrentIndex;
	LerpAnimation m_Lerp;
	
	Sprite m_SelectGameInfo;
	LerpAnimation m_SelectGameLerp;

	Movie m_MoviePlayer;
	Sprite m_Movie;
	TUL::Delay m_MovieStartDelay;

	Sprite m_SelectSummary;
};