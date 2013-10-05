#include "Level2.h"

#include <algorithm>

#include <RingIndex.h>

#include <JoypadDXAdapter.h>
#include <SceneHandler.h>
#include <Button.h>
#include <WaitScene.h>

#include "Level2Menu.h"

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>


struct Level2::Impl{
	Impl(std::function<bool(GameData &)> func) : joypad(0){}
	Level2Menu menu;
	Joypad joypad;
};

Level2::Level2(std::function<bool(GameData &)> func) {
	__impl__ = std::make_shared<Impl>(func);
	auto gameList = GameList(func);
	std::for_each(gameList.begin(), gameList.end(), [&, this](GameData & gameData){
		this->__impl__->menu.addItem(gameData);
	});
}

void Level2::step(
	SceneHandler * sceneStack
){
	auto & j = __impl__->joypad;
	j.update();

	if(j.getButton(AbsJoypad::B).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x39)){
		sceneStack->setNextScene(std::make_shared<WaitScene>(15));
		return;
	}


	sceneStack->setNextScene(sceneStack->getCurrentScene());


	if(j.getButton(AbsJoypad::Up).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x25)){
		__impl__->menu.next();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Level2Menu::Delay));
	}else if(j.getButton(AbsJoypad::Down).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x24)){
		__impl__->menu.prev();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Level2Menu::Delay));
	}
	

	if(j.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x1C)){
		sceneStack->setNextScene(__impl__->menu.select());
	}
}

void Level2::draw(){
	__impl__->menu.draw();
}