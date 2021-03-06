#include "Level2.h"

#include <algorithm>
#include <numeric>

#include <RingIndex.h>

#include <SpriteIrrAdapter.h>
#include <JoypadDXAdapter.h>
#include <SceneHandler.h>
#include <Button.h>
#include <AnalogStick.h>
#include <WaitScene.h>
#include <LerpAnimation.h>

#include "Level2Menu.h"
#include "GameCategory.h"
#include "ConfirmationScreen.h"

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>

#include <Music.h>


struct Level2::Impl{
	Impl(int priority) : menu(priority){
		joypad.emplace_back(0);
		joypad.emplace_back(1);
		joypad.emplace_back(2);
		joypad.emplace_back(3);
	}
	Level2Menu menu;
	std::vector<Joypad> joypad;

	Sprite title;
	LerpAnimation lerp;
	SDLAdapter::GameSE cursor;
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
	__impl__->menu.step();


	using namespace config;

	auto & js = __impl__->joypad;
	std::for_each(js.begin(), js.end(), std::mem_fun_ref(&Joypad::update));

	sceneStack->setNextScene(sceneStack->getCurrentScene());
	

	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j){
			return init || j.getButton(AbsJoypad::B).isJustPressed();
		})
	){
		__impl__->lerp = LerpAnimation(menu::SceneTransDelay/3, 20, 0, []()->double{
			return 20.0;
		});
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::SceneTransDelay/3, [&, sceneStack](int wait){
			if(wait<config::menu::SceneTransDelay/3-1) return;
			sceneStack->loadSceneStack(SceneName::TopMenu);
			sceneStack->setNextScene(std::make_shared<WaitScene>(config::menu::SceneTransDelay*2/3));
		}));
	}


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
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::Delay * (just?2:1)));
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
		sceneStack->setNextScene(std::make_shared<WaitScene>(menu::Delay * (just?2:1)));
	}

	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j){
			return init || j.getButton(AbsJoypad::A).isJustPressed();
		})
	){
		sceneStack->setNextScene(std::make_shared<ConfirmationScreen>(__impl__->menu.select(), 9));
		sceneStack->setNextScene(std::make_shared<WaitScene>(config::menu::SceneTransDelay*2/3));
		std::for_each(js.begin(), js.end(), std::mem_fun_ref(&Joypad::update));
	}
}

void Level2::draw(){
	__impl__->menu.draw();
	
	int animated_pixel = (__impl__->lerp.isAnimating()) ? __impl__->lerp.next() : 0;
	__impl__->title.setPosition(Glas::Vector2i(config::title::X+animated_pixel, config::title::Y));
	__impl__->title.draw();
}