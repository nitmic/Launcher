#pragma once
#include <functional>
#include <tString.h>
class GameData;

class GameCategory{
public:
	std::function<bool(GameData)> getFilter();
	tString getTitleImage_Path();
protected:
	std::function<bool(GameData)> filter;
	tString titleImage_path;
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