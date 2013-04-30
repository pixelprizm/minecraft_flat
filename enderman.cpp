#include "enemies.h"



/** 
*/
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
		double r = std::rand() % 90 + 20;
		double th = (((double)(std::rand()%64))/64)*(2*PI);
		double deltaX = r * std::cos(th);
		double deltaY = r * std::sin(th);
		xPrecise_ += deltaX;
		yPrecise_ += deltaY;
		
		xPrecise_ += (player_->x() - x()) / 10;
		yPrecise_ += (player_->y() - y()) / 10;
		
		// Make sure enderman does not go offscreen
		int halfWidth = pixmap().width()/2;
		int halfHeight = pixmap().height()/2;
		if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ -= deltaX; } // left
		if(yPrecise_ - halfHeight < 0         ) { yPrecise_ -= deltaY; } // top
		if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ -= deltaX; } // right
		if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ -= deltaY; } // bottom
	}
}
