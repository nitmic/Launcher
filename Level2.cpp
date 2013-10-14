#include "Level2.h"

#include <algorithm>

#include <RingIndex.h>

#include <SpriteIrrAdapter.h>
#include <JoypadDXAdapter.h>
#include <SceneHandler.h>
#include <Button.h>
#include <WaitScene.h>

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
};

Level2::Level2(GameCategory category, int priority) : m_Priority(priority) {
	__impl__ = std::make_shared<Impl>(m_Priority);
	auto gameList = GameList(category.getFilter());
	std::for_each(gameList.begin(), gameList.end(), [&, this](GameData & gameData){
		this->__impl__->menu.addItem(gameData);
	});

	__impl__->title.setResouceName(category.getTitleImage_Path());
	__impl__->title.setPriority(9);
	__impl__->title.setPosition(Glas::Vector2i(config::title::X, config::title::Y));
}

void Level2::step(
	SceneHandler * sceneStack
){
	using namespace config::menu;

	auto & j = __impl__->joypad;
	j.update();

	if(j.getButton(AbsJoypad::B).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x39)){
		sceneStack->loadSceneStack(SceneName::TopMenu);
		sceneStack->setNextScene(std::make_shared<WaitScene>(15));
		return;
	}


	sceneStack->setNextScene(sceneStack->getCurrentScene());


	if(j.getButton(AbsJoypad::Up).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x25)){
		__impl__->menu.next();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}else if(j.getButton(AbsJoypad::Down).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x24)){
		__impl__->menu.prev();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}
	

	if(j.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x1C)){
		sceneStack->setNextScene(__impl__->menu.select());
	}
}

void Level2::draw(){
	__impl__->menu.draw();
	__impl__->title.draw();
}