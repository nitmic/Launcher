/*#pragma once
#include <deque>
#include <vector>

#include <tString.h>
#include <MDA.h>
#include <RingIndex.h>
#include <LerpAnimation.h>

#include <SpriteIrrAdapter.h>


class SimpleSlideMenu : public IDrawer{
public:
	void draw();
	void next();
	void prev();
protected:
	virtual void draw_extra() = 0;
private:
	void addItem_base(tString titleImg_path);
	
	std::deque<Sprite> m_Titles;
	std::vector<tString> m_Title_Paths;
	std::vector<Sprite> m_Backgrounds;
	TUL::RingIndex m_CurrentIndex;
	Sprite m_Select;
};*/