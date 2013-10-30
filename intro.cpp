#include "Intro.h"
#include "SceneHandler.h"
#include <enumerate.hpp>
#include "Level1.h"
#include "Level0.h"
#include <WaitScene.h>
#include <GLAS.hpp>
#include <Button.h>

#include <ImageIrrAdapter.h>

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>

IntroScene::IntroScene() : m_Joypad(0){
	using namespace config;

	auto image = std::make_shared<Image>();
	m_MoviePlayer = Movie(image, config::Width, config::Height);
	m_MoviePlayer.open(resource::IntroMovie);
	m_Intro.setResouce(image);
	m_Intro.setPriority(1);
}
void IntroScene::step(SceneHandler * sceneStack){
	m_Joypad.update();
	
	if((!m_MoviePlayer.refresh()) || m_Joypad.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x1C)){
		sceneStack->setNextScene(std::make_shared<Level0>());
		sceneStack->setNextScene(std::make_shared<Level1>());
		sceneStack->saveSceneStack(SceneName::TopMenu);
		return;
	}
	sceneStack->setNextScene(sceneStack->getCurrentScene());
}

void IntroScene::draw(){
	m_Intro.draw();
}