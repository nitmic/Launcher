#include "MenuLevel1.h"
#include "MenuLevel2.h"
#include <SceneHandler.h>
#include <cstdlib>
#include <Joypad.h>
#include <Button.h>
#include <WaitScene.h>


#include <sstream>
#include <tString.h>

MenuLevel1Item::MenuLevel1Item(tString img, std::function<bool(GameData)> func){
	m_Sprite.setResouceName(img);
	m_Sprite.setPriority(1);
	m_Func = func;
}


std::shared_ptr<IScene> MenuLevel1Item::click(){
	return std::make_shared<MenuLevel2>(m_Func);
}

MenuLevel1::MenuLevel1() : m_CurrentIndex(0), m_Joypad(1){
	m_Menu.push_back(MenuLevel1Item(_T(""), [](GameData & game)->bool{
		return true;
	}));
	m_Menu.push_back(MenuLevel1Item(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(0);
	}));
	m_Menu.push_back(MenuLevel1Item(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(1);
	}));
	m_Menu.push_back(MenuLevel1Item(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(2);
	}));
	m_Menu.push_back(MenuLevel1Item(_T(""), [](GameData & game)->bool{
		return game.getNumOfPersonsPlayingGame().at(3);
	}));
	m_Back.setResouceName(_T("kikai.x"));
	m_Back.setPosition(Glas::Vector3f(-30,-50,80));
	m_Back.setScale(0.02f);
}

void MenuLevel1::step(
	SceneHandler * sceneStack
){
	sceneStack->setNextScene(sceneStack->getCurrentScene());

	m_Joypad.update();
	if(m_Joypad.getButton(AbsJoypad::Up).isJustPressed()){
		if(m_CurrentIndex==0) m_CurrentIndex = m_Menu.size();
		--m_CurrentIndex;
		sceneStack->setNextScene(std::make_shared<WaitScene>(20));
	}else if(m_Joypad.getButton(AbsJoypad::Down).isPressed()){
		++m_CurrentIndex;
		if(m_CurrentIndex==m_Menu.size()) m_CurrentIndex = 0;
		sceneStack->setNextScene(std::make_shared<WaitScene>(20));
	}
	

	if(m_Joypad.getButton(AbsJoypad::A).isJustPressed()){
		sceneStack->setNextScene(m_Menu[m_CurrentIndex].click());
		sceneStack->setNextScene(std::make_shared<WaitScene>(60));
	}
	
	{
		toStringStream ostr;
		ostr << m_CurrentIndex;
		GetSingleton<IrrApp>()->accessDevice()->setWindowCaption(ostr.str().c_str());
	}
}

void MenuLevel1::draw(){
	m_Camera.transform();
	m_Back.draw();
}