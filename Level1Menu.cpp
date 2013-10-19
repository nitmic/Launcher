#include "Level1Menu.h"

#include <algorithm>
#include <enumerate.hpp>

#include "Level2.h"
#include "GameList.h"


Level1Menu::Level1Menu(int priority) : m_Priority(priority), m_Titles(config::menu::NumOfMenuItems), m_Bar(priority+1){
	using namespace config;

	std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), [&](Sprite & back){
		back.setResouceName(config::menu::resource::Back_player);
		back.setPriority(m_Priority);
	});
	
	std::for_each(m_Titles.begin(), m_Titles.end(), [&](Sprite & title){
		title.setPriority(m_Priority);
	});

	m_Select.setResouceName(menu::resource::Select);
	m_Select.setPriority(m_Priority+1);
	m_Select.setPosition(Glas::Vector2i(menu::X, menu::Y+menu::SelectItemOrder*menu::ItemHeight));
	
	m_Info.setPriority(4);
}

void Level1Menu::selectItemUpdate(){
	m_Info.setResouceName(m_Info_Paths[m_CurrentIndex]);
	m_InfoLerp = LerpAnimation(config::menu::Delay, 0, 20, [this]() -> double{
		return 0;
	});
}

void Level1Menu::addItem(tString itemImg_path, GameCategory category, tString infoImg_path){
	m_Info_Paths.push_back(infoImg_path);
	m_Filters.push_back(category);
	m_Title_Paths.push_back(itemImg_path);

	m_CurrentIndex = TUL::RingIndex(m_Filters.size());
	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		using namespace config;
		title.setResouceName(m_Title_Paths[m_CurrentIndex-menu::SelectItemOrder+i]);
	}));
	
	selectItemUpdate();
}

void Level1Menu::next(){
	using namespace config;

	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(m_Title_Paths[m_CurrentIndex+(menu::LastItemOrder-menu::SelectItemOrder)+1]);
	m_Titles.push_back(title);
	m_CurrentIndex++;

	lerp = LerpAnimation(menu::Delay, -menu::ItemHeight, 0, [&, this]()->double{
		this->m_Titles.pop_front();
		return 0;
	});
	
	selectItemUpdate();
	m_Bar.setPosition((double)m_CurrentIndex/(double)m_Filters.size());
}

void Level1Menu::prev(){
	using namespace config;

	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(m_Title_Paths[m_CurrentIndex-menu::SelectItemOrder-1]);
	m_Titles.push_front(title);
	m_CurrentIndex--;

	lerp = LerpAnimation(menu::Delay, 0, -menu::ItemHeight, [&, this]()->double{
		this->m_Titles.pop_back();
		return 0;
	});
	
	selectItemUpdate();
	m_Bar.setPosition((double)m_CurrentIndex/(double)m_Filters.size());
}

std::shared_ptr<IScene> Level1Menu::select(){
	return std::make_shared<Level2>(m_Filters[m_CurrentIndex], m_Priority);
}

void Level1Menu::draw(){

	int animated_pixel = (lerp.isAnimating()) ? lerp.next() : 0;

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
	
	
	m_Bar.draw();
	m_Select.draw();

	
	{
		int animated_pixel = (m_InfoLerp.isAnimating()) ? m_InfoLerp.next() : 0;
		m_Info.setPosition(Glas::Vector2i(config::info::X+animated_pixel, config::info::Y));
		m_Info.draw();
	}
}