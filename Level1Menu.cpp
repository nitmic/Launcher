#include "Level1Menu.h"

#include <algorithm>
#include <enumerate.hpp>

#include "Level2.h"
#include "GameList.h"

static const int TitleSize = 50;
static const int DrawX = 500;
static const int DrawY = 0;
static const int SelectItemOrder = Level1Menu::NumOfTitles/2;
static const int LastItemOrder = Level1Menu::NumOfTitles-1;

static const tString BackgroundImg_path = _T("MenuBackground.png");
static const tString SelectImg_path = _T("select.png");

Level1Menu::Level1Menu() : m_Titles(NumOfTitles){
	std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), [&](Sprite & back){
		back.setResouceName(BackgroundImg_path);
		back.setPriority(2);
	});
	
	std::for_each(m_Titles.begin(), m_Titles.end(), [&](Sprite & title){
		title.setPriority(2);
	});

	m_Select.setResouceName(SelectImg_path);
	m_Select.setPriority(3);
	m_Select.setPosition(Glas::Vector2i(DrawX, DrawY+SelectItemOrder*TitleSize));
}

void Level1Menu::addItem(tString titleImg_path, std::function<bool(GameData)> filter){
	m_Filters.push_back(filter);
	m_Title_Paths.push_back(titleImg_path);

	m_CurrentIndex = TUL::RingIndex(m_Filters.size());
	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		title.setResouceName(m_Title_Paths[m_CurrentIndex-SelectItemOrder+i]);
	}));

}

void Level1Menu::next(){
	Sprite title;
	title.setPriority(2);
	title.setResouceName(m_Title_Paths[m_CurrentIndex+(LastItemOrder-SelectItemOrder)+1]);
	m_Titles.push_back(title);
	m_CurrentIndex++;

	lerp = LerpAnimation(Delay, -TitleSize, 0, [&, this]()->double{
		this->m_Titles.pop_front();
		return 0;
	});
}

void Level1Menu::prev(){
	Sprite title;
	title.setPriority(2);
	title.setResouceName(m_Title_Paths[m_CurrentIndex-SelectItemOrder-1]);
	m_Titles.push_front(title);
	m_CurrentIndex--;

	lerp = LerpAnimation(Delay, 0, -TitleSize, [&, this]()->double{
		this->m_Titles.pop_back();
		return 0;
	});
}

std::shared_ptr<IScene> Level1Menu::select(){
	return std::make_shared<Level2>(m_Filters[m_CurrentIndex]);
}

void Level1Menu::draw(){
	int animated_pixel = (lerp.isAnimating()) ? lerp.next() : 0;

	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		title.setPosition(Glas::Vector2i(DrawX, DrawY+i*TitleSize+animated_pixel));
		title.draw();
	}));
	
	std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), TUL::enumerate<void>([&,this](Sprite & back, int i){
		back.setPosition(Glas::Vector2i(DrawX, DrawY+i*TitleSize+animated_pixel));
		back.draw();
	}));

	m_Select.draw();
}