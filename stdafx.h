#pragma once
namespace IrrAdapter{};
using namespace IrrAdapter;

namespace DXAdapter{
	class Joypad;
};
using DXAdapter::Joypad;

enum SceneName{
	TopMenu
};

#include <tString.h>
namespace{
	namespace config{
		const int Width = 800;
		const int Height = 600;
		const std::string SettingFileName = "GameData.json";
		
		namespace resource{
			const tString Background = _T("./Image/Background/Background.png");
			const tString MovieBack = _T("./Image/Background/Background_movie.png");
			const tString SummaryBack = _T("./Image/Background/Background_summary.png");
			const tString Belt = _T("./Image/Background/Belt.png");
			const tString SpaceStation = _T("./Mesh/taka2.x");
			const std::string IntroMovie = "./Movie/titan.ogg";
		};

		namespace title{
			const int X = 375;
			const int Y = 55;
			namespace resource{
				const tString Title = _T("./Image/Title/GameSelect.png");
				const tString AllGames = _T("./Image/Title/AllGames.png");
				const tString OnePlayer = _T("./Image/Title/1PlayerGame.png");
				const tString TwoPlayer = _T("./Image/Title/2PlayerGame.png");
				const tString ThreePlayer = _T("./Image/Title/3PlayerGame.png");
				const tString FourPlayer = _T("./Image/Title/4PlayerGame.png");
			};
		};

		namespace menu{
			const int Delay = 3;
			const int X = 500;
			const int Y = 0;
			const int ItemHeight = 50;
			const int NumOfMenuItems = 13;
			const int SelectItemOrder = NumOfMenuItems/2;
			const int LastItemOrder = NumOfMenuItems-1;

			namespace scrollbar{
				const int Y = 60;
				const int X = 765;
				const int Height = 420;
				namespace resource{
					const tString ScrollButton = _T("./Image/Menu/ScrollButton.png");
					const tString ScrollBar = _T("./Image/Menu/ScrollBar.png");
				};
			};

			namespace resource{
				const tString AllGames = _T("./Image/Menu/Category_ALLGames.png");
				const tString OnePlayer = _T("./Image/Menu/Category_1Player.png");
				const tString TwoPlayer = _T("./Image/Menu/Category_2Player.png");
				const tString ThreePlayer = _T("./Image/Menu/Category_3Player.png");
				const tString FourPlayer = _T("./Image/Menu/Category_4Player.png");

				const tString Back_category = _T("./Image/Menu/Background_category.png");
				const tString Back_player = _T("./Image/Menu/Background_player.png");
				const tString Back_game = _T("./Image/Menu/Background_game.png");
				const tString Select = _T("./Image/Menu/Select.png");
			};
		}

		namespace marquee{
			const int Y = 565;
			const int X = 0;
			const int Speed = 640;
			
			const int Width = 1224;
			namespace resource{
				const tString Marquee = _T("./Image/Marquee.png");
			};
		};
	};

};