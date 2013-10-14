#include "GameList.h"

#include <assert.h>
#include <algorithm>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "picojson.hpp"


namespace{
	std::vector<GameData> g_GameList;
}

void GameListInit(const std::string dir){
	assert(boost::filesystem::is_directory(dir));
	g_GameList.clear();

	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(dir); it!=end; ++it){
		if(!boost::filesystem::is_directory(*it)) continue;
		
		auto jsonPath = it->path() / config::SettingFileName;
		if(!boost::filesystem::is_regular_file(jsonPath)) continue;

		std::ifstream ifs(jsonPath.c_str());
		auto json = std::make_shared<picojson::value>();
		picojson::parse(*json, ifs);
		
		g_GameList.push_back(GameData(json, it->path().string()));
	}
}

std::vector<GameData> GameList(std::function<bool(GameData &)> func){
	std::vector<GameData> v(g_GameList.size());
	auto it = std::copy_if(g_GameList.begin(), g_GameList.end(), v.begin(), func);
	v.resize(std::distance(v.begin(),it));  // shrink container to new size
	return v;
}

std::string GameData::getGameGenre() const{
	return m_Data->get("genre").to_str();
}

std::string GameData::getSummaryImagePath() const{
	auto name = boost::filesystem::path(m_Data->get("resource").get("summary").to_str());
	return (boost::filesystem::path(m_Directory) / name).string();
}

std::string GameData::getMenuImagePath() const{
	auto name = boost::filesystem::path(m_Data->get("resource").get("menu").to_str());
	return (boost::filesystem::path(m_Directory) / name).string();
}

std::string GameData::getSampleVideoPath() const{
	auto name = boost::filesystem::path(m_Data->get("resource").get("sampleVideo").to_str());
	return (boost::filesystem::path(m_Directory) / name).string();
}

std::string GameData::getInfoImagePath() const{
	auto name = boost::filesystem::path(m_Data->get("resource").get("info").to_str());
	return (boost::filesystem::path(m_Directory) / name).string();
}

std::string GameData::getGameExeFilePath() const{
	auto name = boost::filesystem::path(m_Data->get("exe").to_str());
	return (boost::filesystem::path(m_Directory) / name).string();
}

std::bitset<4> GameData::getNumOfPersonsPlayingGame() const{
	std::bitset<4> numOfPersons;

	auto & l = m_Data->get("numOfPersons").get<picojson::array>();
	for(auto it=l.begin(); it!=l.end(); ++it){
		int v = it->get<double>();
		assert(v>=1&&v<=4);
		numOfPersons.set(v-1);
	}
	return numOfPersons;
}

