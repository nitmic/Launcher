#include "Level0.h"

#include <SpriteIrrAdapter.h>
#include <BackgroundIrrAdapter.h>
#include <3DObjectIrrAdapter.h>
#include <Camera.h>
#include <CameraIrrAdapter.hpp>

#include "Marquee.h"


struct Level0::Impl{
	Impl() : marquee(9){}
	Background background;
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

	__impl__->line.setResouceName(resource::Belt);
	__impl__->line.setPriority(8);
	__impl__->gameSelect.setResouceName(title::resource::Title);
	__impl__->gameSelect.setPriority(9);

	__impl__->object3d.setResouceName(resource::SpaceStation);
	__impl__->object3d.setPosition(Glas::Vector3f(-10,-50,70));
	__impl__->object3d.setScale(0.02f);
}

void Level0::draw(){
	__impl__->camera.transform();
	__impl__->object3d.draw();
	__impl__->background.draw();
	
	__impl__->line.draw();
	__impl__->gameSelect.draw();
	__impl__->marquee.draw();
}