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

#include <tString.hpp>
namespace{
	namespace config{
		const int Width = 800;
		const int Height = 600;
		const std::string SettingFileName = "GameData.json";
		
		namespace resource{
			const TUL::tString Background = _T("./Image/Background/Background.png");
			const TUL::tString MovieBack = _T("./Image/Background/Background_movie.png");
			const TUL::tString SummaryBack = _T("./Image/Background/Background_summary.png");
			const TUL::tString Belt = _T("./Image/Background/Belt.png");
			const TUL::tString SpaceStation = _T("./Mesh/taka2.x");
			const std::string IntroMovie = "./Movie/titan.ogg";
		};
		
		namespace title{
			const int X = 375;
			const int Y = 55;
			namespace resource{
				const TUL::tString Title = _T("./Image/Title/GameSelect.png");
				const TUL::tString AllGames = _T("./Image/Title/AllGames.png");
				const TUL::tString OnePlayer = _T("./Image/Title/1PlayerGame.png");
				const TUL::tString TwoPlayer = _T("./Image/Title/2PlayerGame.png");
				const TUL::tString ThreePlayer = _T("./Image/Title/3PlayerGame.png");
				const TUL::tString FourPlayer = _T("./Image/Title/4PlayerGame.png");
			};
		};

		namespace info{
			const int X = 20;
			const int Y = 100;
			namespace resource{
				const TUL::tString AllGames = _T("./Image/Menu/Info_AllGames.png");
				const TUL::tString OnePlayer = _T("./Image/Menu/Info_1Player.png");
				const TUL::tString TwoPlayer = _T("./Image/Menu/Info_2Player.png");
				const TUL::tString ThreePlayer = _T("./Image/Menu/Info_3Player.png");
				const TUL::tString FourPlayer = _T("./Image/Menu/Info_4Player.png");
			};
		};

		namespace menu{
			const int Delay = 4;
			const int SceneTransDelay = 15;
			const int X = 500;
			const int Y = 0;
			const int ItemHeight = 40;
			const int NumOfMenuItems = 15;
			const int SelectItemOrder = NumOfMenuItems/2;
			const int LastItemOrder = NumOfMenuItems-1;

			namespace scrollbar{
				const int Y = 60;
				const int X = 765;
				const int Height = 420;
				namespace resource{
					const TUL::tString ScrollButton = _T("./Image/Menu/ScrollButton.png");
					const TUL::tString ScrollBar = _T("./Image/Menu/ScrollBar.png");
				};
			};

			namespace resource{
				const TUL::tString AllGames = _T("./Image/Menu/Category_ALLGames.png");
				const TUL::tString OnePlayer = _T("./Image/Menu/Category_1Player.png");
				const TUL::tString TwoPlayer = _T("./Image/Menu/Category_2Player.png");
				const TUL::tString ThreePlayer = _T("./Image/Menu/Category_3Player.png");
				const TUL::tString FourPlayer = _T("./Image/Menu/Category_4Player.png");

				const TUL::tString Back_category = _T("./Image/Menu/Background_category.png");
				const TUL::tString Back_player = _T("./Image/Menu/Background_player.png");
				const TUL::tString Back_game = _T("./Image/Menu/Background_game.png");
				const TUL::tString Select = _T("./Image/Menu/Select.png");
			};
		}

		namespace marquee{
			const int Y = 565;
			const int X = 0;
			const int Speed = 640;
			
			const int Width = 1224;
			namespace resource{
				const TUL::tString Marquee = _T("./Image/Marquee.png");
			};
		};
	};

};