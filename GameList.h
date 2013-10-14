#pragma once
#include <memory>
#include <string>
#include <bitset>
#include <vector>
#include <functional>


namespace picojson{
	class value;
};

class GameData{
public:
	GameData(){}
	GameData(std::shared_ptr<picojson::value> json, std::string directory) : m_Data(json), m_Directory(directory){}
	std::string getGameGenre() const;
	std::string getMenuImagePath() const;
	std::string getSummaryImagePath() const;
	std::string getInfoImagePath() const;
	std::string getSampleVideoPath() const;
	std::string getGameExeFilePath() const;
	std::bitset<4> getNumOfPersonsPlayingGame() const;
private:
	std::string m_Directory;
	std::shared_ptr<picojson::value> m_Data;
};



void GameListInit(const std::string dir);
std::vector<GameData> GameList(std::function<bool(GameData &)> func);
