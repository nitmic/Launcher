#include "Level2Menu.h"

#include <algorithm>
#include <enumerate.hpp>

Level2Menu::Level2Menu(int priority) : m_Priority(priority), m_Titles(config::menu::NumOfMenuItems), m_Bar(priority+1){
	using namespace config;

	std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), [&](Sprite & back){
		back.setResouceName(config::menu::resource::Back_game);
		back.setPriority(m_Priority);
	});
	
	std::for_each(m_Titles.begin(), m_Titles.end(), [&](Sprite & title){
		title.setPriority(m_Priority);
	});

	m_Select.setResouceName(menu::resource::Select);
	m_Select.setPriority(m_Priority+1);
	m_Select.setPosition(Glas::Vector2i(menu::X, menu::Y+menu::SelectItemOrder*menu::ItemHeight));

	m_SelectGameInfo.setPriority(3);
}


void Level2Menu::addItem(GameData gameData){
	m_GameList.push_back(gameData);

	m_CurrentIndex = TUL::RingIndex(m_GameList.size());

	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		using namespace config;
		auto path = m_GameList[m_CurrentIndex-menu::SelectItemOrder+i].getMenuImagePath();
		tString tPath(path.begin(), path.end());
		title.setResouceName(tPath);
	}));
	addSelectItemUpdate();
	/*
	auto path = m_GameList[m_CurrentIndex].getInfoImagePath();
	tString tPath(path.begin(), path.end());
	m_SelectGameInfo.setResouceName(tPath);
	*/
}

void Level2Menu::addSelectItemUpdate(){
	auto path = m_GameList[m_CurrentIndex].getInfoImagePath();
	tString tPath(path.begin(), path.end());
	m_SelectGameInfo.setResouceName(tPath);
	m_SelectGameLerp = LerpAnimation(config::menu::Delay, 0, 20, []() -> double{
		return 0;
	});
}


void Level2Menu::next(){
	using namespace config;

	auto data = m_GameList[m_CurrentIndex+(menu::LastItemOrder-menu::SelectItemOrder)+1];
	auto path = data.getMenuImagePath();
	tString tPath(path.begin(), path.end());

	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(tPath);
	m_Titles.push_back(title);
	m_CurrentIndex++;

	m_Lerp = LerpAnimation(menu::Delay, -menu::ItemHeight, 0, [&, this]()->double{
		this->m_Titles.pop_front();
		return 0;
	});
	
	addSelectItemUpdate();
	m_Bar.setPosition((double)m_CurrentIndex/(double)m_GameList.size());
}

void Level2Menu::prev(){
	using namespace config;

	auto path = m_GameList[m_CurrentIndex-menu::SelectItemOrder-1].getMenuImagePath();
	tString tPath(path.begin(), path.end());

	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(tPath);
	m_Titles.push_front(title);
	m_CurrentIndex--;

	m_Lerp = LerpAnimation(menu::Delay, 0, -menu::ItemHeight, [&, this]()->double{
		this->m_Titles.pop_back();
		return 0;
	});
	
	addSelectItemUpdate();
	m_Bar.setPosition((double)m_CurrentIndex/(double)m_GameList.size());
}


std::shared_ptr<IScene> Level2Menu::select(){
	//auto path = "\"" + m_GameList[m_CurrentIndex].getGameExeFilePath() + "\"";
	//system(path.c_str());
	//system("C:\\notepad.exe");
	return nullptr;
}

void Level2Menu::draw(){
	
	{
		int animated_pixel = (m_Lerp.isAnimating()) ? m_Lerp.next() : 0;
	
		std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
			using namespace config;
			title.setPosition(Glas::Vector2i(menu::X+30, menu::Y+i*menu::ItemHeight+animated_pixel));
			title.draw();
		}));
		
		std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), TUL::enumerate<void>([&,this](Sprite & back, int i){
			using namespace config;
			back.setPosition(Glas::Vector2i(menu::X, menu::Y+i*menu::ItemHeight+animated_pixel));
			back.draw();
		}));
	}

	m_Bar.draw();
	m_Select.draw();

	{
		int animated_pixel = (m_SelectGameLerp.isAnimating()) ? m_SelectGameLerp.next() : 0;
		m_SelectGameInfo.setPosition(Glas::Vector2i(20+animated_pixel, 100));
		m_SelectGameInfo.draw();
	}
}