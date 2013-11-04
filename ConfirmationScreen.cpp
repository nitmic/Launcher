#include "ConfirmationScreen.h"


#include <SceneHandler.h>
#include <JoypadDXAdapter.h>
#include <Button.h>
#include <MDAUtility.hpp>
#include <SpriteIrrAdapter.h>
#include <WaitScene.h>
#include <RingIndex.h>
#include <Delay.h>

#include <IrrAdapter.h>
#include <FakeFullScreen.h>
#include <boost/filesystem/path.hpp>

// debug
#include <Singleton.hpp>
#include <DXKeyboard.h>

#include <Music.h>

struct ConfirmationScreen::Impl{
	Impl() : joypad(0),ri(2){}
	Joypad joypad;
	SDLAdapter::GameSE cursor_se;
	TUL::RingIndex ri;
	Sprite image;
	Sprite cursor;
	int cursorX;
	TUL::tString exe_path;
	TUL::Delay cursorAnimation;
};


ConfirmationScreen::ConfirmationScreen(TUL::tString exe_path, int priority){
	__impl__ = std::make_shared<Impl>();
	__impl__->exe_path = exe_path;
	__impl__->ri = 1;

	__impl__->image.setPriority(priority);
	__impl__->image.setResouceName(_T("confirmation.png"));
	__impl__->image.setPosition(Glas::Vector2i(150,100));
	
	__impl__->cursor.setPriority(priority);
	__impl__->cursor.setResouceName(_T("cursor.png"));
	setCursorAnimation();
}
void ConfirmationScreen::exec(){
	SDLAdapter::ReserveTune(std::make_shared<SDLAdapter::Silent>());
	SDLAdapter::PlayTune();

	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	
	TUL::restoreFakeFullScreen(GetSingleton<IrrApp>()->accessHWND());
	while(!IsIconic(GetSingleton<IrrApp>()->accessHWND())) ShowWindow(GetSingleton<IrrApp>()->accessHWND(), SW_MINIMIZE);

	//	Processì¬
	TUL::tString dirPath = boost::filesystem::path(__impl__->exe_path).parent_path().c_str();
	assert(CreateProcess(__impl__->exe_path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, dirPath.c_str(), &si, &pi));
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	TUL::fakeFullScreen(GetSingleton<IrrApp>()->accessHWND(), config::Width, config::Height);
	return;
}

void ConfirmationScreen::step(
	SceneHandler * sceneStack
){
	using config::menu::Delay;
	using config::menu::SceneTransDelay;

	__impl__->joypad.update();

	if(__impl__->joypad.getButton(AbsJoypad::A).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x1C)){
		if(__impl__->ri==0){
			exec();
			sceneStack->loadSceneStack(SceneName::TopMenu);
		}
		sceneStack->setNextScene(std::make_shared<WaitScene>(60));
		return;
	}

	if(__impl__->joypad.getButton(AbsJoypad::B).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isPressed(0x39)){
		sceneStack->setNextScene(std::make_shared<WaitScene>(60));
		return;
	}

	sceneStack->setNextScene(sceneStack->getCurrentScene());
	if(__impl__->joypad.getButton(AbsJoypad::Up).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x25)){
		__impl__->cursor_se.ring(_T("./Sound/guard.wav"));
		__impl__->ri--;
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}else if(__impl__->joypad.getButton(AbsJoypad::Down).isJustPressed() || GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x24)){
		__impl__->cursor_se.ring(_T("./Sound/guard.wav"));
		__impl__->ri++;
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay));
	}

}

void ConfirmationScreen::setCursorAnimation(){
	__impl__->cursorX = 30;
	__impl__->cursorAnimation = TUL::Delay(30, [this](){
		this->__impl__->cursorX = 50;
		auto my = this;
		this->__impl__->cursorAnimation = TUL::Delay(30, [my](){
			my->setCursorAnimation();
		});
	});
}
void ConfirmationScreen::draw(){

	__impl__->cursor.setPosition(Glas::Vector2i(__impl__->cursorX + 200, 150+65*__impl__->ri + 100));
	__impl__->cursor.draw();

	__impl__->image.draw();

	__impl__->cursorAnimation.step();
}