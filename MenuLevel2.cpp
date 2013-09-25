#include "MenuLevel2.h"

#include <SceneHandler.h>
#include <Joypad.h>
#include <Button.h>
#include <WaitScene.h>

#include <IrrAdapter.h>
#include <tString.h>


void MenuLevel2::step(
	SceneHandler * sceneStack
){
	if(m_Joypad.getButton(AbsJoypad::B).isJustPressed()){
		sceneStack->setNextScene(std::make_shared<WaitScene>(60));
		return;
	}
	sceneStack->setNextScene(sceneStack->getCurrentScene());

	m_Joypad.update();
	if(m_Joypad.getButton(AbsJoypad::Up).isPressed()){
		if(m_CurrentIndex==0) m_CurrentIndex = m_GameList.size();
		--m_CurrentIndex;
		sceneStack->setNextScene(std::make_shared<WaitScene>(20));
	}else if(m_Joypad.getButton(AbsJoypad::Down).isPressed()){
		++m_CurrentIndex;
		if(m_CurrentIndex==m_GameList.size()) m_CurrentIndex = 0;
		sceneStack->setNextScene(std::make_shared<WaitScene>(20));
	}
	
	if(m_Joypad.getButton(AbsJoypad::A).isJustPressed()){
		sceneStack->setNextScene(std::make_shared<WaitScene>(120));
		//auto path = "\"" + m_GameList[m_CurrentIndex].getGameExeFilePath() + "\"";
		//system(path.c_str());
		system("C:\\notepad.exe");
	}
	

	
	{
		auto title = m_GameList[m_CurrentIndex].getGameTitle();
		GetSingleton<IrrApp>()->accessDevice()->setWindowCaption(tString(title.begin(), title.end()).c_str());
	}

}

void MenuLevel2::draw(){}