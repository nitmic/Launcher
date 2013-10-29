#include <DXManager.h>
#include <DXInput.h>
#include <DXKeyboard.h>
#include <Singleton.hpp>
#include <FakeFullScreen.h>
#include "IrrAdapter.h"
#include "GameLoop.h"
#include "Intro.h"
#include "GameList.h"

#ifdef WIN32
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main()
#endif
{
	auto app = GetSingleton<IrrApp>();
	if(!app->Setup(config::Width, config::Height)) return 1;
	app->accessDevice()->getCursorControl()->setVisible(false);
	TUL::fakeFullScreen(app->accessHWND(), config::Width, config::Height);

	//Joypad & sound—p
	{
		auto hWnd = app->accessHWND();
		if(!GetSingleton<DXLib::DXManager>()->Setup(hWnd, config::Width, config::Height, true)) return 1;
		if(!GetSingleton<DXLib::DXInput>()->Setup(hInst, hWnd)) return 1;
	}
	GameListInit("Games");
	
	GameLoop gameLoop(std::make_shared<IntroScene>());
	app->setOnFrameUpdate([&]()->bool{
		GetSingleton<DXLib::DXInput>()->Update();
		if(GetSingleton<DXLib::DXKeyboard>()->isJustPressed(0x01)) return false; 
		return gameLoop.update();
	});
	app->setOnFrameDraw([&](){
		gameLoop.draw();
	});

	app->AppLoop();

	return 0;
}