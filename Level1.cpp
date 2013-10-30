#include "Level1.h"


#include <SceneHandler.h>
#include <JoypadDXAdapter.h>
#include <Button.h>
#include <MDAUtility.hpp>
#include <SpriteIrrAdapter.h>
#include <WaitScene.h>

#include "Level1Menu.h"
#include "GameList.h"

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>

#include <Music.h>

struct Level1::Impl{
	Impl() : joypad(0), menu(0){}
	Level1Menu menu;
	Joypad joypad;
	SDLAdapter::GameSE cursor;
};


Level1::Level1(){
	using namespace config::menu;

	__impl__ = std::make_shared<Impl>();
	__impl__->menu.addItem(resource::AllGames, AllGames());
	__impl__->menu.addItem(resource::OnePlayer, OnePlayer(), config::info::resource::OnePlayer);
	__impl__->menu.addItem(resource::TwoPlayer, TwoPlayer(), config::info::resource::TwoPlayer);
	__impl__->menu.addItem(resource::ThreePlayer, ThreePlayer(), config::info::resource::ThreePlayer);
	__impl__->menu.addItem(resource::FourPlayer, FourPlayer(), config::info::resource::FourPlayer);
}

void Level1::step(
	SceneHandler * sceneStack
){
	using config::menu::Delay;
	using config::menu::SceneTransDelay;

	__impl__->joypad.update();

	if(__impl__->joypad.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x1C)){
		sceneStack->setNextScene(__impl__->menu.select());
		sceneStack->setNextScene(std::make_shared<WaitScene>(SceneTransDelay));
		return;
	}
	

	sceneStack->setNextScene(sceneStack->getCurrentScene());

	if(__impl__->joypad.getButton(AbsJoypad::Up).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x25)){
		__impl__->cursor.ring(_T("./Sound/guard.wav"));
		__impl__->menu.next();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}else if(__impl__->joypad.getButton(AbsJoypad::Down).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x24)){
		__impl__->cursor.ring(_T("./Sound/guard.wav"));
		__impl__->menu.prev();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}
}

void Level1::draw(){
	__impl__->menu.draw();
}