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
	double speed = (std::rand()%16)/8 + .25; // random speed from .25 to 2.25
	double theta = (((double)(std::rand()%64))/64)*(2*PI); // random angle
	vX_ = speed * std::cos(theta);
	vY_ = speed * std::sin(theta);
}

/** Moves the creeper. Creepers move continuously in a direction, bouncing off of the gameSpace's walls
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Creeper::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	// Move the creeper
	xPrecise_ += vX_;
	yPrecise_ += vY_;
	
	// Make sure creeper does not go offscreen; switch its direction if it does
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	if(xPrecise_ - halfWidth  < 0         ) { vX_ = -vX_; xPrecise_+=vX_; } // left
	if(yPrecise_ - halfHeight < 0         ) { vY_ = -vY_; yPrecise_+=vY_; } // top
	if(xPrecise_ + halfWidth  > windowMaxX) { vX_ = -vX_; xPrecise_+=vX_; } // right
	if(yPrecise_ + halfHeight > windowMaxY) { vY_ = -vY_; yPrecise_+=vY_; } // bottom
}
