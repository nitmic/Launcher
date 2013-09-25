#include "Intro.h"
#include "SceneHandler.h"
#include <enumerate.hpp>
#include "MenuLevel1.h"
#include <WaitScene.h>
#include <GLAS.hpp>
#include <Button.h>

IntroScene::IntroScene() : m_Joypad(0){
	m_Intro.open("titan.ogg");
}
void IntroScene::step(SceneHandler * sceneStack){
	m_Joypad.update();
	
	if((!m_Intro.refresh()) || m_Joypad.getButton(AbsJoypad::A).isJustPressed()){
		sceneStack->setNextScene(std::make_shared<MenuLevel1>());
		return;
	}
	sceneStack->setNextScene(sceneStack->getCurrentScene());
}

void IntroScene::draw(){
	m_Intro.draw();
}