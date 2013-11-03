#pragma once

#include <IScene.h>

class SceneHandler;

class ConfirmationScreen : public IScene{
public:
	ConfirmationScreen(TUL::tString exe_path, int priority);
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	void exec();
	bool isTransparency(){return true;};
private:
	void setCursorAnimation();
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};