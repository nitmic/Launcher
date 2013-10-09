#include "Level1.h"


#include <SceneHandler.h>
#include <JoypadDXAdapter.h>
#include <Button.h>
#include <MDAUtility.hpp>
#include <BackgroundIrrAdapter.h>
#include <SpriteIrrAdapter.h>
#include <3DObjectIrrAdapter.h>
#include <Camera.h>
#include <CameraIrrAdapter.hpp>
#include <WaitScene.h>

#include "Level1Menu.h"
#include "GameList.h"

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>

struct Level1::Impl{
	Impl() : joypad(0){}
	Level1Menu menu;
	Background background;
	Sprite line;
	Sprite gameSelect; 

	Drawer3DImpl object3d;
	Camera<DefaultCamera> camera;
	Joypad joypad;
};


Level1::Level1(){
	__impl__ = std::make_shared<Impl>();
	__impl__->menu.addItem(_T("ALLGames.png"), [](GameData & game)->bool{
		return true;
	});
	__impl__->menu.addItem(_T("OnePlayer.png"), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(0);
	});
	
	__impl__->menu.addItem(_T("TwoPlayers.png"), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(1);
	});
	/*
	__impl__->menu.addItem(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(2);
	});
	__impl__->menu.addItem(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(3);
	});*/

	__impl__->background.setResouceName(
		_T("background.png"),
		_T("background.png"),
		_T("background.png"),
		_T("background.png"),
		_T("background.png"),
		_T("background.png")
	);

	__impl__->line.setResouceName(_T("Line.png"));
	__impl__->line.setPriority(5);
	__impl__->gameSelect.setResouceName(_T("GameSelect.png"));
	__impl__->gameSelect.setPriority(6);

	__impl__->object3d.setResouceName(_T("taka2.x"));
	__impl__->object3d.setPosition(Glas::Vector3f(-10,-50,70));
	__impl__->object3d.setScale(0.02f);
}

void Level1::step(
	SceneHandler * sceneStack
){
	sceneStack->setNextScene(sceneStack->getCurrentScene());

	__impl__->joypad.update();


	if(__impl__->joypad.getButton(AbsJoypad::Up).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x25)){
		__impl__->menu.next();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Level1Menu::Delay));
	}else if(__impl__->joypad.getButton(AbsJoypad::Down).isPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x24)){
		__impl__->menu.prev();
		sceneStack->setNextScene(std::make_shared<WaitScene>(Level1Menu::Delay));
	}
	

	if(__impl__->joypad.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x1C)){
		sceneStack->setNextScene(__impl__->menu.select());
		sceneStack->setNextScene(std::make_shared<WaitScene>(15));
	}
}

void Level1::draw(){
	__impl__->camera.transform();
	__impl__->object3d.draw();
	__impl__->background.draw();
	__impl__->menu.draw();
	__impl__->line.draw();
	__impl__->gameSelect.draw();
}