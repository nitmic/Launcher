#pragma once
#include <functional>
#include <IScene.h>

class SceneHandler;
class GameData;
class GameCategory;

class Level2 : public IScene{
public:
	Level2(GameCategory category, int priority);
	void step(
		SceneHandler * sceneStack
	);
	void draw();
	bool isTransparency(){return true;};
private:
	int m_Priority;

	struct Impl;
	std::shared_ptr<Impl> __impl__;
};