#include "GameCategory.h"

#include "GameList.h"


std::function<bool(GameData)> GameCategory::getFilter(){
	return filter;
}

tString GameCategory::getTitleImage_Path(){
	return titleImage_path;
}


AllGames::AllGames(){
	filter = [](GameData & game)->bool{return true;};
	titleImage_path = config::title::resource::AllGames;
}

OnePlayer::OnePlayer(){
	filter =  [](GameData & game)->bool{return game.getNumOfPersonsPlayingGame().at(0);};
	titleImage_path = config::title::resource::OnePlayer;
}

TwoPlayer::TwoPlayer(){
	filter =  [](GameData & game)->bool{return game.getNumOfPersonsPlayingGame().at(1);};
	titleImage_path = config::title::resource::TwoPlayer;
}

ThreePlayer::ThreePlayer(){
	filter =  [](GameData & game)->bool{return game.getNumOfPersonsPlayingGame().at(2);};
	titleImage_path = config::title::resource::ThreePlayer;
}

FourPlayer::FourPlayer(){
	filter =  [](GameData & game)->bool{return game.getNumOfPersonsPlayingGame().at(3);};
	titleImage_path = config::title::resource::FourPlayer;
}