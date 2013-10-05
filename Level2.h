#pragma once
#include <functional>
#include <IScene.h>

class SceneHandler;
class GameData;

class Level2 : public IScene{
public:
	Level2(std::function<bool(GameData &)> func);
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return true;};
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};