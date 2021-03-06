#pragma once
#include <array>
#include <deque>
#include <vector>
#include <functional>

#include <tString.hpp>
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
	void addItem(TUL::tString itemImg_path, GameCategory func, TUL::tString infoImg_path=_T("blank.png"));

	void next();
	void prev();

	void draw();
	std::shared_ptr<IScene> select();
private:
	void selectItemUpdate();
	std::vector<GameCategory> m_Filters;
	std::vector<TUL::tString> m_Info_Paths;

	std::deque<Sprite> m_Titles;
	std::vector<TUL::tString> m_Title_Paths;
	std::array<Sprite, config::menu::NumOfMenuItems> m_Backgrounds;
	Sprite m_Select;
	ScrollBar m_Bar;

	int m_Priority;
	TUL::RingIndex m_CurrentIndex;
	LerpAnimation lerp;

	Sprite m_Info;
	LerpAnimation m_InfoLerp;
};
