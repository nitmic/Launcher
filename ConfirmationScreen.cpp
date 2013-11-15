#include "ConfirmationScreen.h"

#include <numeric>
#include <SceneHandler.h>
#include <JoypadDXAdapter.h>
#include <Button.h>
#include <AnalogStick.h>
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
	Impl() : ri(2){
		joypad.emplace_back(0);
		joypad.emplace_back(1);
		joypad.emplace_back(2);
		joypad.emplace_back(3);
	}
	std::vector<Joypad> joypad;
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

	auto & js = __impl__->joypad;
	std::for_each(js.begin(), js.end(), std::mem_fun_ref(&Joypad::update));

	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j){
			return init || j.getButton(AbsJoypad::A).isJustPressed();
		})
	){
		if(__impl__->ri==0){
			exec();
			sceneStack->loadSceneStack(SceneName::TopMenu);
		}
		sceneStack->setNextScene(std::make_shared<WaitScene>(SceneTransDelay));
		return;
	}


	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j){
			return init || j.getButton(AbsJoypad::B).isJustPressed();
		})
	){
		sceneStack->setNextScene(std::make_shared<WaitScene>(SceneTransDelay));
		return;
	}

	sceneStack->setNextScene(sceneStack->getCurrentScene());
	if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			auto stick = j.getLStick().getTilt().getAngle();
			return init || j.getButton(AbsJoypad::Up).isJustPressed() || (70.f < stick && stick < 110.f && j.getLStick().getTilt().getLength() > 0.6);
		})
	){
		__impl__->cursor_se.ring(_T("./Sound/guard.wav"));
		__impl__->ri--;
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay*2));
	}else if(
		std::accumulate(js.begin(), js.end(), false, [](bool init, Joypad & j)->bool{
			auto stick = j.getLStick().getTilt().getAngle();
			return init || j.getButton(AbsJoypad::Down).isJustPressed() || (250.f < stick && stick < 290.f && j.getLStick().getTilt().getLength() > 0.6);
		})
	){
		__impl__->cursor_se.ring(_T("./Sound/guard.wav"));
		__impl__->ri++;
		sceneStack->setNextScene(std::make_shared<WaitScene>(Delay*2));
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