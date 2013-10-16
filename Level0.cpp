#include "Level0.h"

#include <SpriteIrrAdapter.h>
#include <BackgroundIrrAdapter.h>
#include <3DObjectIrrAdapter.h>
#include <Camera.h>
#include <CameraIrrAdapter.hpp>
#include <lightIrrAdapter.h>

#include "Marquee.h"


struct Level0::Impl{
	Impl() : marquee(9){}
	Background background;
	Sprite movieBack;
	Sprite summaryBack;
	Sprite line;
	Sprite gameSelect; 
	Marquee marquee;

	Drawer3DImpl object3d;
	Camera<DefaultCamera> camera;
};

Level0::Level0(){
	using namespace config;

	__impl__ = std::make_shared<Impl>();
	__impl__->background.setResouceName(
		resource::Background,
		resource::Background,
		resource::Background,
		resource::Background,
		resource::Background,
		resource::Background
	);
	
	__impl__->summaryBack.setResouceName(resource::SummaryBack);
	__impl__->summaryBack.setPriority(0);
	__impl__->summaryBack.setPosition(Glas::Vector2i(125,265));
	__impl__->movieBack.setResouceName(resource::MovieBack);
	__impl__->movieBack.setPriority(0);
	__impl__->movieBack.setPosition(Glas::Vector2i(20, 100));
	__impl__->line.setResouceName(resource::Belt);
	__impl__->line.setPriority(8);
	__impl__->gameSelect.setResouceName(title::resource::Title);
	__impl__->gameSelect.setPriority(9);

	__impl__->object3d.setResouceName(resource::SpaceStation);
	__impl__->object3d.setPosition(Glas::Vector3f(-10,-50,70));
	__impl__->object3d.setScale(0.02f);
}

void Level0::draw(){
	Glas::Vector3f p = __impl__->camera.getPosition() + Glas::Vector3f(0, -0.1, 0.15);
	__impl__->camera.setPosition(p);

	__impl__->camera.transform();
	__impl__->object3d.draw();
	__impl__->background.draw();
	
	__impl__->line.draw();
	__impl__->gameSelect.draw();
	__impl__->marquee.draw();

	__impl__->summaryBack.draw();
	__impl__->movieBack.draw();

}