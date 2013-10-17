#include "Level2.h"

#include <algorithm>

#include <RingIndex.h>

#include <SpriteIrrAdapter.h>
#include <JoypadDXAdapter.h>
#include <SceneHandler.h>
#include <Button.h>
#include <WaitScene.h>
#include <LerpAnimation.h>

#include "Level2Menu.h"
#include "GameCategory.h"

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>


struct Level2::Impl{
	Impl(int priority) : joypad(0), menu(priority){}
	Level2Menu menu;
	Joypad joypad;

	Sprite title;
	LerpAnimation lerp;
};

Level2::Level2(GameCategory category, int priority) : m_Priority(priority) {
	__impl__ = std::make_shared<Impl>(m_Priority);
	auto gameList = GameList(category.getFilter());
	std::for_each(gameList.begin(), gameList.end(), [&, this](GameData & gameData){
		this->__impl__->menu.addItem(gameData);
	});

	__impl__->title.setResouceName(category.getTitleImage_Path());
	__impl__->title.setPriority(9);
	__impl__->lerp = LerpAnimation(config::menu::SceneTransDelay/3, 0, 20, []() -> double{
		return 0;
	});
}

void Level2::step(
	SceneHandler * sceneStack
){
	using namespace config;

	auto & j = __impl__->joypad;
	j.update();

	sceneStack->setNextScene(sceneStack->getCurrentScene());
	

	if(j.getButton(AbsJoypad::B).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x39)){
		__impl__->lerp = LerpAnimation(menu::SceneTransDelay/3, 20, 0, []()->double{
			return 20.0;
		});
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::SceneTransDelay/3, [&, sceneStack](int wait){
			if(wait<config::menu::SceneTransDelay/3-1) return;
			sceneStack->loadSceneStack(SceneName::TopMenu);
			sceneStack->setNextScene(std::make_shared<WaitScene>(config::menu::SceneTransDelay*2/3));
		}));
	}


	if(j.getButton(AbsJoypad::Up).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x25)){
		__impl__->menu.next();
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::Delay));
	}else if(j.getButton(AbsJoypad::Down).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x24)){
		__impl__->menu.prev();
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::Delay));
	}
	

	if(j.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x1C)){
		__impl__->menu.select();
	}

	__impl__->menu.step();
}

void Level2::draw(){
	__impl__->menu.draw();
	
	int animated_pixel = (__impl__->lerp.isAnimating()) ? __impl__->lerp.next() : 0;
	__impl__->title.setPosition(Glas::Vector2i(config::title::X+animated_pixel, config::title::Y));
	__impl__->title.draw();
}