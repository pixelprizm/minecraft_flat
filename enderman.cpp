// Copyright (C) 2013 Eric Gauderman



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
void Enderman::updatePrecisePos(const int& windowMaxX, const int& windowMaxY)
{
	if(std::rand()%80 == 0)
	{
		double r = std::rand() % 90 + 25;
		double th = ((std::rand()%64)/64.0)*(2.0*PI);
		double deltaX = r * std::cos(th);
		double deltaY = r * std::sin(th);
		xPrecise_ += deltaX;
		yPrecise_ += deltaY;
		
		xPrecise_ += (player_->x() - x()) / 8.0;
		yPrecise_ += (player_->y() - y()) / 8.0;
		
		// Make sure enderman does not go offscreen (no bounce)
		checkEdgesSlide(windowMaxX, windowMaxY);
	}
}
