#include "ScrollBar.h"
ScrollBar::ScrollBar(int priority) : currentPos_percent(0){
	using namespace config::menu::scrollbar;

	bar.setResouceName(resource::ScrollBar);
	bar.setPriority(priority);
	bar.setPosition(Glas::Vector2i(X, Y));

	button.setResouceName(resource::ScrollButton);
	button.setPriority(priority);
}

void ScrollBar::setPosition(double percent){
	using namespace config;
	int height = menu::scrollbar::Height;

	lerp = LerpAnimation(menu::Delay, percent*height, currentPos_percent*height, [&, this, height]() -> double{
		return this->currentPos_percent*height;
	});
	currentPos_percent = percent;
}

void ScrollBar::draw(){
	using namespace config::menu::scrollbar;
	int animated_pixel = (lerp.isAnimating()) ? lerp.next() : this->currentPos_percent * Height;

	button.setPosition(Glas::Vector2i(X, Y+animated_pixel));
	button.draw();

	bar.draw();
}