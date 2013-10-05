#pragma once

#include <IScene.h>

class SceneHandler;


class Level1 : public IScene{
public:
	Level1();
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return false;};
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};