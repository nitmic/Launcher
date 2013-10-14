#pragma once
#include <array>
#include <deque>
#include <vector>
#include <functional>

#include <tString.h>
#include <RingIndex.h>
#include <LerpAnimation.h>

#include <SpriteIrrAdapter.h>

#include "GameCategory.h"
#include "ScrollBar.h"


class GameData;

class IScene;

class Level1Menu{
public:
	Level1Menu(int priority);
	void addItem(tString itemImg_path, GameCategory func);

	void next();
	void prev();

	void draw();
	std::shared_ptr<IScene> select();
private:
	std::vector<GameCategory> m_Filters;
	std::deque<Sprite> m_Titles;
	std::vector<tString> m_Title_Paths;
	std::array<Sprite, config::menu::NumOfMenuItems> m_Backgrounds;
	Sprite m_Select;
	ScrollBar m_Bar;

	int m_Priority;
	TUL::RingIndex m_CurrentIndex;
	LerpAnimation lerp;
};
