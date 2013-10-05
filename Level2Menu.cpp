#include "Level2Menu.h"

#include <algorithm>
#include <enumerate.hpp>

static const int TitleSize = 50;
static const int DrawX = 500;
static const int DrawY = 0;
static const int SelectItemOrder = Level2Menu::NumOfTitles/2;
static const int LastItemOrder = Level2Menu::NumOfTitles-1;

static const tString BackgroundImg_path = _T("MenuBackground.png");
static const tString SelectImg_path = _T("select.png");

Level2Menu::Level2Menu() : m_Titles(NumOfTitles){
	std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), [&](Sprite & back){
		back.setResouceName(BackgroundImg_path);
		back.setPriority(4);
	});
	
	std::for_each(m_Titles.begin(), m_Titles.end(), [&](Sprite & title){
		title.setPriority(4);
	});

	m_Select.setResouceName(SelectImg_path);
	m_Select.setPriority(5);
	m_Select.setPosition(Glas::Vector2i(DrawX, DrawY+SelectItemOrder*TitleSize));
}


void Level2Menu::addItem(GameData gameData){
	m_GameList.push_back(gameData);

	m_CurrentIndex = TUL::RingIndex(m_GameList.size());

	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		auto path = m_GameList[m_CurrentIndex-SelectItemOrder+i].getGameTitle();
		tString tPath(path.begin(), path.end());
		title.setResouceName(tPath);
	}));
}

void Level2Menu::next(){
	auto data = m_GameList[m_CurrentIndex+(LastItemOrder-SelectItemOrder)+1];
	auto path = data.getGameTitle();
	tString tPath(path.begin(), path.end());

	Sprite title;
	title.setPriority(4);
	title.setResouceName(tPath);
	m_Titles.push_back(title);
	m_CurrentIndex++;

	lerp = LerpAnimation(Delay, -TitleSize, 0, [&, this]()->double{
		this->m_Titles.pop_front();
		return 0;
	});
}

void Level2Menu::prev(){
	auto path = m_GameList[m_CurrentIndex-SelectItemOrder-1].getGameTitle();
	tString tPath(path.begin(), path.end());

	Sprite title;
	title.setPriority(4);
	title.setResouceName(tPath);
	m_Titles.push_front(title);
	m_CurrentIndex--;

	lerp = LerpAnimation(Delay, 0, -TitleSize, [&, this]()->double{
		this->m_Titles.pop_back();
		return 0;
	});
}


std::shared_ptr<IScene> Level2Menu::select(){
	//auto path = "\"" + m_GameList[m_CurrentIndex].getGameExeFilePath() + "\"";
	//system(path.c_str());
	//system("C:\\notepad.exe");
	return nullptr;
}

void Level2Menu::draw(){
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