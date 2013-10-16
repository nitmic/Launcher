#include "Intro.h"
#include "SceneHandler.h"
#include <enumerate.hpp>
#include "Level1.h"
#include "Level0.h"
#include <WaitScene.h>
#include <GLAS.hpp>
#include <Button.h>

#include <ImageIrrAdapter.h>

IntroScene::IntroScene() : m_Joypad(0), m_MovieDecoder(config::Width, config::Height){
	using namespace config;
	m_MovieDecoder.open(resource::IntroMovie);
	m_Intro.setPriority(1);
}
void IntroScene::step(SceneHandler * sceneStack){
	m_Joypad.update();
	
	//if((!m_MovieDecoder.refresh()) || m_Joypad.getButton(AbsJoypad::A).isJustPressed()){
		sceneStack->setNextScene(std::make_shared<Level0>());
		sceneStack->setNextScene(std::make_shared<Level1>());
		sceneStack->saveSceneStack(SceneName::TopMenu);
		return;
	//}
	m_Intro.setResouce(m_MovieDecoder.decode());
	sceneStack->setNextScene(sceneStack->getCurrentScene());
}

void IntroScene::draw(){
	m_Intro.draw();
}