#include "Level2Menu.h"

#include <algorithm>
#include <enumerate.hpp>
#include <ImageIrrAdapter.h>
#include <FakeFullScreen.h>

#include <Music.h>

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
	m_Select.setPriority(m_Priority);
	m_Select.setPosition(Glas::Vector2i(menu::X+20, menu::Y+menu::SelectItemOrder*menu::ItemHeight));

	m_SelectGameInfo.setPriority(4);
	
	auto image = std::make_shared<Image>();
	m_MoviePlayer =Movie(image, 300, 225);
	m_Movie.setResouce(image);
	m_Movie.setPriority(3);
	m_Movie.setPosition(Glas::Vector2i(info::X+2, info::Y+2));

	m_SelectSummary.setPosition(Glas::Vector2i(125,265));
	m_SelectSummary.setPriority(4);
}


void Level2Menu::addItem(GameData gameData){
	m_GameList.push_back(gameData);

	m_CurrentIndex = TUL::RingIndex(m_GameList.size());

	std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
		using namespace config;
		title.setResouceName(TUL::to_tstring(m_GameList[m_CurrentIndex-menu::SelectItemOrder+i].getMenuImagePath()));
	}));
	addSelectItemUpdate();
}

void Level2Menu::addSelectItemUpdate(){
	m_SelectGameInfo.setResouceName(TUL::to_tstring(m_GameList[m_CurrentIndex].getInfoImagePath()));
	m_SelectGameLerp = LerpAnimation(config::menu::Delay, 0, 20, [this]() -> double{
		return 0;
	});
	
	m_MovieStartDelay = TUL::Delay(config::menu::Delay+5 ,[this](){
			this->m_MoviePlayer.open(this->m_GameList[this->m_CurrentIndex].getSampleVideoPath());
			this->m_SelectSummary.setResouceName(TUL::to_tstring(
				this->m_GameList[this->m_CurrentIndex].getSummaryImagePath()
			));
	});
}

void Level2Menu::next(){
	using namespace config;
	
	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(TUL::to_tstring(
		m_GameList[m_CurrentIndex+(menu::LastItemOrder-menu::SelectItemOrder)+1].getMenuImagePath()
	));
	m_Titles.push_back(title);
	m_CurrentIndex++;
	
	m_Lerp = LerpAnimation(menu::Delay, -menu::ItemHeight, 0, [&, this]()->double{
		this->m_Titles.pop_front();
		return 0;
	});
	
	addSelectItemUpdate();
	m_Bar.setPosition(((double)-m_CurrentIndex)/((double)m_GameList.size()-1));
}

void Level2Menu::prev(){
	using namespace config;

	Sprite title;
	title.setPriority(m_Priority);
	title.setResouceName(TUL::to_tstring(m_GameList[m_CurrentIndex-menu::SelectItemOrder-1].getMenuImagePath()));
	m_Titles.push_front(title);
	m_CurrentIndex--;

	m_Lerp = LerpAnimation(menu::Delay, 0, -menu::ItemHeight, [&, this]()->double{
		this->m_Titles.pop_back();
		return 0;
	});
	
	addSelectItemUpdate();
	m_Bar.setPosition(((double)-m_CurrentIndex)/((double)m_GameList.size()-1));
}

void Level2Menu::step(){
	if(m_MovieStartDelay.isActive()) m_MovieStartDelay.step();
	
	if(!m_MoviePlayer.refresh()){
		m_MoviePlayer.open(m_GameList[m_CurrentIndex].getSampleVideoPath());
		return;
	}
	
	if(!m_MovieStartDelay.isActive()){
		m_Movie.draw();
		m_SelectSummary.draw();
	}
}

TUL::tString Level2Menu::select(){
	return TUL::to_tstring(m_GameList[m_CurrentIndex].getGameExeFilePath());
}

void Level2Menu::draw(){
	{
		int animated_pixel = (m_Lerp.isAnimating()) ? m_Lerp.next() : 0;
	
		std::for_each(m_Titles.begin(), m_Titles.end(), TUL::enumerate<void>([&,this](Sprite & title, int i){
			using namespace config;
			title.setPosition(Glas::Vector2i(menu::X+30, menu::Y+i*menu::ItemHeight+animated_pixel));
			title.draw();
		}));
		
		m_Select.draw();
		
		std::for_each(m_Backgrounds.begin(), m_Backgrounds.end(), TUL::enumerate<void>([&,this](Sprite & back, int i){
			using namespace config;
			back.setPosition(Glas::Vector2i(menu::X, menu::Y+i*menu::ItemHeight+animated_pixel));
			back.draw();
		}));
	}

	m_Bar.draw();

	{
		int animated_pixel = (m_SelectGameLerp.isAnimating()) ? m_SelectGameLerp.next() : 0;
		m_SelectGameInfo.setPosition(Glas::Vector2i(config::info::X+animated_pixel, config::info::Y));
		m_SelectGameInfo.draw();
	}
}