#pragma once
#include <functional>
#include <tString.hpp>
class GameData;

class GameCategory{
public:
	std::function<bool(GameData)> getFilter();
	TUL::tString getTitleImage_Path();
protected:
	std::function<bool(GameData)> filter;
	TUL::tString titleImage_path;
};

struct AllGames : public GameCategory{
	AllGames();
};

struct OnePlayer : public GameCategory{
	OnePlayer();
};

struct TwoPlayer : public GameCategory{
	TwoPlayer();
};

struct ThreePlayer : public GameCategory{
	ThreePlayer();
};

struct FourPlayer : public GameCategory{
	FourPlayer();
};


struct ActionGames : public GameCategory{
	ActionGames();
};

struct PartyGames : public GameCategory{
	PartyGames();
};

struct BattleGames : public GameCategory{
	BattleGames();
};

struct TableGames : public GameCategory{
	TableGames();
};