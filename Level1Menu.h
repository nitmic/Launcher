#pragma once
#include <array>
#include <deque>
#include <vector>
#include <functional>

#include <tString.h>
#include <RingIndex.h>
#include <LerpAnimation.h>

#include <SpriteIrrAdapter.h>

class GameData;

class IScene;

class Level1Menu{
public:
	enum{
		Delay = 3,
		NumOfTitles = 13 // äÔêîå¿íË
	};

	Level1Menu();
	void addItem(tString titleImg_path, std::function<bool(GameData)> func);

	void next();
	void prev();

	void draw();
	std::shared_ptr<IScene> select();
private:
	std::vector<std::function<bool(GameData)>> m_Filters;
	std::deque<Sprite> m_Titles;
	std::vector<tString> m_Title_Paths;
	std::array<Sprite, NumOfTitles> m_Backgrounds;
	Sprite m_Select;
	TUL::RingIndex m_CurrentIndex;
	LerpAnimation lerp;
};