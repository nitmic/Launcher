#include "GameCategory.h"

#include "GameList.h"


std::function<bool(GameData)> GameCategory::getFilter(){
	return filter;
}

TUL::tString GameCategory::getTitleImage_Path(){
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
#include <algorithm>
ActionGames::ActionGames(){
	filter =  [](GameData & game)->bool{
		auto genres = game.getGenre();
		return std::find(genres.begin(), genres.end(), "Action")!=genres.end();
	};
	titleImage_path = config::title::resource::Action;
}

PartyGames::PartyGames(){
	filter =  [](GameData & game)->bool{
		auto genres = game.getGenre();
		return std::find(genres.begin(), genres.end(), "Party")!=genres.end();
	};
	titleImage_path = config::title::resource::Party;
}

BattleGames::BattleGames(){
	filter =  [](GameData & game)->bool{
		auto genres = game.getGenre();
		return std::find(genres.begin(), genres.end(), "VS")!=genres.end();
	};
	titleImage_path = config::title::resource::Battle;
}

TableGames::TableGames(){
	filter =  [](GameData & game)->bool{
		auto genres = game.getGenre();
		return std::find(genres.begin(), genres.end(), "Command")!=genres.end();
	};
	titleImage_path = config::title::resource::Table;
}