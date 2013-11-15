#include "Level1.h"

#include <numeric>
#include <SceneHandler.h>
#include <JoypadDXAdapter.h>
#include <Button.h>
#include <AnalogStick.h>
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
	Impl() : menu(0){
		joypad.emplace_back(0);
		joypad.emplace_back(1);
		joypad.emplace_back(2);
		joypad.emplace_back(3);
	}
	Level1Menu menu;
	std::vector<Joypad> joypad;
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
	__impl__->menu.addItem(resource::Action, ActionGames(), config::info::resource::Action);
	__impl__->menu.addItem(resource::Party, PartyGames(), config::info::resource::Party);
	__impl__->menu.addItem(resource::Battle, BattleGames(), config::info::resource::Battle);
	__impl__->menu.addItem(resource::Table, TableGames(), config::info::resource::Table);
}

void Level1::step(
	SceneHandler * sceneStack
){
	using config::menu::Delay;
	using config::menu::SceneTransDelay;
	
	auto & js = __impl__->joypad;
	std::for_each(js.begin(), js.end(), std::mem_fun_ref(&Joypad::update));
	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j){
			return init || j.getButton(AbsJoypad::A).isJustPressed();
		}) || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x1C)
	){
		sceneStack->setNextScene(__impl__->menu.select());
		sceneStack->setNextScene(std::make_shared<WaitScene>(SceneTransDelay));
		return;
	}
	

	sceneStack->setNextScene(sceneStack->getCurrentScene());

	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			auto stick = j.getLStick().getTilt().getAngle();
			return init || j.getButton(AbsJoypad::Up).isPressed() || (70.f < stick && stick < 110.f && j.getLStick().getTilt().getLength() > 0.6);
		})
	){
		__impl__->cursor.ring(_T("./Sound/guard.wav"));
		__impl__->menu.prev();
		auto just = std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			return init || j.getButton(AbsJoypad::Up).isJustPressed();
		});
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay * (just?2:1)));
	}else if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			auto stick = j.getLStick().getTilt().getAngle();
			return init || j.getButton(AbsJoypad::Down).isPressed() || (250.f < stick && stick < 290.f && j.getLStick().getTilt().getLength() > 0.6);
		})
	){
		__impl__->cursor.ring(_T("./Sound/guard.wav"));
		__impl__->menu.next();
		auto just = std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			return init || j.getButton(AbsJoypad::Down).isJustPressed();
		});
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay * (just?2:1)));
	}
}

void Level1::draw(){
	__impl__->menu.draw();
}