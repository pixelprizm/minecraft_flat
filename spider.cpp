#include "enemies.h"



/** Constructor. Calls Thing constructor and initially randomizes the velocity.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item
*/
Spider::Spider(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	randomizeVel();
}

/** Reset the velocity of the spider to a random speed and direction
*/
void Spider::randomizeVel()
{
	double speed = (double)((std::rand()%24))/8; // random speed from 0 to 3
	double theta = (((double)(std::rand()%64))/64)*(2*PI); // random angle
	vX_ = speed * std::cos(theta);
	vY_ = speed * std::sin(theta);
}

/** Update the position for spiders. Spiders move and will sometimes change directions
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Spider::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	// Random chance of changing direction
	if(std::rand()%64==0)
	{
		randomizeVel();
	}
	
	// Move the spider
	xPrecise_ += vX_;
	yPrecise_ += vY_;
	
	// Make sure spider does not go offscreen; switch its direction if it does
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	if(xPrecise_ - halfWidth  < 0         ) { vX_ = -vX_; xPrecise_+=vX_; } // left
	if(yPrecise_ - halfHeight < 0         ) { vY_ = -vY_; yPrecise_+=vY_; } // top
	if(xPrecise_ + halfWidth  > windowMaxX) { vX_ = -vX_; xPrecise_+=vX_; } // right
	if(yPrecise_ + halfHeight > windowMaxY) { vY_ = -vY_; yPrecise_+=vY_; } // bottom
}
