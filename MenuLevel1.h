#pragma once
#include <IScene.h>
#include <functional>
#include <tString.h>
#include "GameList.h"
#include <SpriteIrrAdapter.h>
#include <3DObjectIrrAdapter.h>
#include <MDA.h>
#include <Camera.h>
#include <CameraIrrAdapter.hpp>
#include <lightIrrAdapter.h>
#include <JoypadDXAdapter.h>
#include <BackgroundIrrAdapter.h>

class MenuLevel1Item : public IDrawer{
public:
	MenuLevel1Item(){};
	MenuLevel1Item(tString img, std::function<bool(GameData)> func);
	void draw(){m_Sprite.draw();};
	bool isVisible(){return true;};
	std::shared_ptr<IScene> click();
private:
	std::function<bool(GameData)> m_Func;
	Sprite m_Sprite;
};

class MenuLevel1 : public IScene{
public:
	MenuLevel1();
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return false;};
private:
	std::vector<MenuLevel1Item> m_Menu;
	int m_CurrentIndex;
	Background m_Background;
	Drawer3DImpl m_Back;
	Camera<DefaultCamera> m_Camera;
	Joypad m_Joypad;
};