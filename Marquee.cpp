#include "Marquee.h"
#include <algorithm>
#include <GLAS.hpp>
#include <enumerate.hpp>


Marquee::Marquee(int priority){
	std::for_each(m_Image.begin(), m_Image.end(), [&,this](Sprite & image){
		image.setPriority(priority);
		image.setResouceName(config::marquee::resource::Marquee);
	});
	using namespace config;
	m_Animation = LerpAnimation(marquee::Speed, -marquee::Width, 0, [&, this]() -> double{
		this->m_Animation.restart();
		return 0;
	});
}

void Marquee::draw(){
	int animated_pixel = (m_Animation.isAnimating()) ? m_Animation.next() : 0;
	std::for_each(m_Image.begin(), m_Image.end(), TUL::enumerate<void>([&,this](Sprite & image, int i){
		image.setPosition(Glas::Vector2i(i*config::marquee::Width + animated_pixel + config::marquee::X, config::marquee::Y));
		image.draw();
	}));
}