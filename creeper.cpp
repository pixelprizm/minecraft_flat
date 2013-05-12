// Copyright (C) 2013 Eric Gauderman



#include "enemies.h"



/** Constructor. Calls Thing constructor and initializes velocity to a random speed and direction.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item
*/
Creeper::Creeper(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	double speed = (std::rand()%32)/16.0 + .25; // random speed from .25 to 2.25
	double theta = ((std::rand()%64)/64.0)*(2.0*PI); // random angle
	vX_ = speed * std::cos(theta);
	vY_ = speed * std::sin(theta);
}

/** Moves the creeper. Creepers move continuously in a direction, bouncing off of the gameSpace's walls
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Creeper::updatePrecisePos(const int& windowMaxX, const int& windowMaxY)
{
	// Move the creeper
	xPrecise_ += vX_;
	yPrecise_ += vY_;
	
	// Make sure creeper does not go offscreen (bounce)
	checkEdgesBounce(windowMaxX, windowMaxY, vX_, vY_);
}
