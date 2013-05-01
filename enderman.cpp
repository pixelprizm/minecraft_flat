#include "enemies.h"



/** Constructor. Calls Thing constructor.  Endermen have no speed properties to initialize.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item, used for motion
*/
Enderman::Enderman(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	
}

/** Updates enderman's position. Endermen teleport within a limited radius, a random distance in a random direction.
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Enderman::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	if(std::rand()%80 == 0)
	{
		double r = std::rand() % 90 + 25;
		double th = (((double)(std::rand()%64))/64)*(2*PI);
		double deltaX = r * std::cos(th);
		double deltaY = r * std::sin(th);
		xPrecise_ += deltaX;
		yPrecise_ += deltaY;
		
		xPrecise_ += (player_->x() - x()) / 8;
		yPrecise_ += (player_->y() - y()) / 8;
		
		// Make sure enderman does not go offscreen
		int halfWidth = pixmap().width()/2;
		int halfHeight = pixmap().height()/2;
		if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ -= deltaX; } // left
		if(yPrecise_ - halfHeight < 0         ) { yPrecise_ -= deltaY; } // top
		if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ -= deltaX; } // right
		if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ -= deltaY; } // bottom
	}
}
