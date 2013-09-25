#pragma once
#include <functional>
#include <IScene.h>
#include "GameList.h"
#include <JoypadDXAdapter.h>

class MenuLevel2 : public IScene{
public:
	MenuLevel2(std::function<bool(GameData &)> func) : m_GameList(GameList(func)), m_Joypad(1), m_CurrentIndex(0){};
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return true;};
private:
	int m_CurrentIndex;
	std::vector<GameData> m_GameList;
	Joypad m_Joypad;
};