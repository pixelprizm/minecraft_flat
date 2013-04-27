#include "enemies.h"



Enderman::Enderman(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	
}

/** 
*/
void Enderman::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	if(std::rand()%100 == 0)
	{
		double r = std::rand() % 90 + 5;
		double th = (((double)(std::rand()%64))/64)*(2*PI);
		double deltaX = r * std::cos(th);
		double deltaY = r * std::sin(th);
		xPrecise_ += deltaX;
		yPrecise_ += deltaY;
		// Check for going outside the map
		if(xPrecise_<0) { deltaX = -deltaX; xPrecise_+=deltaX; }
		if(yPrecise_<0) { deltaY = -deltaY; yPrecise_+=deltaY; }
		if(xPrecise_+pixmap().width()  > windowMaxX) { deltaX = -deltaX; xPrecise_+=deltaX; }
		if(yPrecise_+pixmap().height() > windowMaxY) { deltaY = -deltaY; yPrecise_+=deltaY; }
	}
}
