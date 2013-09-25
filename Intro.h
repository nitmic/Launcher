#pragma once
#include <memory>

#include "IScene.h"
#include <SpriteIrrAdapter.h>
#include <MovieIrrAdapter.h>
#include <JoypadDXAdapter.h>

class WaitScene;

class IntroScene : public IScene{
public:
	IntroScene();
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return false;};
private:
	Movie m_Intro;
	Joypad m_Joypad;
};