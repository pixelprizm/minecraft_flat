#include "enemies.h"



/** Constructor for spider
*/
Spider::Spider(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	randomizeVel();
}

/** Reset the velocity of the spider to a random value
*/
void Spider::randomizeVel()
{
	double speed = (std::rand()%16)/8 + 1; // random speed from 1 to 3
	double theta = (((double)(std::rand()%64))/64)*(2*PI); // random angle
	vX_ = speed * std::cos(theta);
	vY_ = speed * std::sin(theta);
	
	
	
	//vX_ = ( (std::rand()%16)/8 + 1 ) * ( (std::rand()%2)*2-1 );
	//vY_ = ( (std::rand()%16)/8 + 1 ) * ( (std::rand()%2)*2-1 );
	//      ^random value from 1 to 3   ^randomly switches to negative
}

/** Update the position for spiders. Spiders move very slowly and will sometimes change directions
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
