#include "Level0.h"

#include <SpriteIrrAdapter.h>
#include <BackgroundIrrAdapter.h>
#include <3DObjectIrrAdapter.h>
#include <Camera.h>
#include <CameraIrrAdapter.hpp>
#include <lightIrrAdapter.h>
#include <Delay.h>
#include <Music.h>
#include <MDA.h>

#include "Marquee.h"

struct Station : public I3DAgent{
	Glas::Vector3f getPosition(){
		return Glas::Vector3f(-10, -10, 70);
	}
	Glas::Quaternion getAttitude(){
		return Glas::Quaternion(0, 1, 0, 1);
	}
	bool isAlive(){return true;}
	void step(){};
};

struct Level0::Impl{
	Impl() : marquee(9){}
	Background background;
	Sprite movieBack;
	Sprite summaryBack;
	Sprite line;
	Sprite gameSelect; 
	Marquee marquee;

	Drawer3DImpl object3d;
	std::shared_ptr<ICamera> camera;

	std::shared_ptr<SDLAdapter::Tune> bgm;
	Sprite keyInfo;
	TUL::Delay keyInfoAnimation;

	TUL::Delay cameraWorkRoutine;
	std::function<void(void)> cameraWork;
};

Level0::Level0(){
	using namespace config;
	__impl__ = std::make_shared<Impl>();
	__impl__->bgm = std::make_shared<SDLAdapter::Tune>(_T("./Sound/SelectMenu.wav"));
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
	
	__impl__->keyInfo.setPosition(Glas::Vector2i(450,0));
	__impl__->keyInfo.setPriority(9);
	setKeyInfoAnimation();
	setCameraWork();
}

void Level0::setCameraWork(){
	auto camera = std::make_shared<Camera<DefaultCamera>>();
	__impl__->camera = camera;
	camera->setPosition(Glas::Vector3f(0,0,0));
	__impl__->cameraWork = [camera](){
		Glas::Vector3f p = camera->getPosition() + Glas::Vector3f(0, -0.05, 0.075);
		camera->setPosition(p);
	};
	__impl__->cameraWorkRoutine = TUL::Delay(600, [this](){
		auto my = this;
		auto camera = std::make_shared<Camera<TPSCamera>>();
		camera->setTarget(std::make_shared<Station>());
		camera->setDistance(60);
		my->__impl__->camera = camera;
		my->__impl__->cameraWork = [my,camera](){
			camera->rotate(0.1, Glas::Vector3f(0, 1, 0.1));
		};
		my->__impl__->cameraWorkRoutine = TUL::Delay(600, [my](){
			auto camera = std::make_shared<Camera<DefaultCamera>>();
			camera->setPosition(Glas::Vector3f(0,-30,60));
			my->__impl__->camera = camera;
			my->__impl__->cameraWork = [camera](){
				Glas::Vector3f p = camera->getPosition() + Glas::Vector3f(0, 0.015, -0.08);
				camera->setPosition(p);
			};

			auto self = my;
			my->__impl__->cameraWorkRoutine = TUL::Delay(1000, [self](){
				self->setCameraWork();
			});
		});
	});
}

void Level0::setKeyInfoAnimation(){
	__impl__->keyInfo.setResouceName(_T("./Image/keyInfo_Off.png"));
	__impl__->keyInfoAnimation = TUL::Delay(30, [this](){
		this->__impl__->keyInfo.setResouceName(_T("./Image/keyInfo_On.png"));
		auto my = this;
		__impl__->keyInfoAnimation = TUL::Delay(30, [my](){
			my->setKeyInfoAnimation();
		});
	});
}

void Level0::draw(){
	SDLAdapter::ReserveTune(__impl__->bgm);
	__impl__->keyInfoAnimation.step();
	__impl__->keyInfo.draw();

	__impl__->cameraWork();
	__impl__->camera->transform();

	__impl__->object3d.draw();
	__impl__->background.draw();
	
	__impl__->line.draw();
	__impl__->gameSelect.draw();
	__impl__->marquee.draw();

	__impl__->summaryBack.draw();
	__impl__->movieBack.draw();

	__impl__->cameraWorkRoutine.step();
}