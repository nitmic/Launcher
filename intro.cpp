#include "Intro.h"
#include "SceneHandler.h"
#include <enumerate.hpp>
#include "Level1.h"
#include "Level0.h"
#include <WaitScene.h>
#include <GLAS.hpp>
#include <Button.h>

IntroScene::IntroScene() : m_Joypad(0){
	using namespace config;
	m_Intro.open(resource::IntroMovie);
}
void IntroScene::step(SceneHandler * sceneStack){
	m_Joypad.update();
	
	//if((!m_Intro.refresh()) || m_Joypad.getButton(AbsJoypad::A).isJustPressed()){
		sceneStack->setNextScene(std::make_shared<Level0>());
		sceneStack->setNextScene(std::make_shared<Level1>());
		sceneStack->saveSceneStack(SceneName::TopMenu);
		return;
	//}
	//sceneStack->setNextScene(sceneStack->getCurrentScene());
}

void IntroScene::draw(){
	m_Intro.draw();
}