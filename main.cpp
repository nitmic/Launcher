#include <DXManager.h>
#include <DXInput.h>
#include <Singleton.hpp>
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
	if(!app->Setup()) return 1;

	//Joypad & sound—p
	{
		auto hWnd = app->accessHWND();
		if(!GetSingleton<DXLib::DXManager>()->Setup(hWnd, 800, 600, true)) return 1;
		if(!GetSingleton<DXLib::DXInput>()->Setup(hInst, hWnd)) return 1;
	}
	GameListInit("./Games");
	
	auto v = GameList([](GameData & g){return true;});

	GameLoop gameLoop(std::make_shared<IntroScene>());
	app->setOnFrameUpdate([&]()->bool{
		GetSingleton<DXLib::DXInput>()->Update();
		return gameLoop.update();
	});
	app->setOnFrameDraw([&](){
		gameLoop.draw();
	});

	app->AppLoop();
	return 0;
}