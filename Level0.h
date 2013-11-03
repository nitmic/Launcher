#pragma once

#include <IScene.h>

class SceneHandler;


class Level0 : public IScene{
public:
	Level0();
	void step(
		SceneHandler * sceneStack
	){};
	void draw();
	bool isTransparency(){return false;};
private:
	void setKeyInfoAnimation();
	void setCameraWork();

	struct Impl;
	std::shared_ptr<Impl> __impl__;
};