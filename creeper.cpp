#include "enemies.h"



/** 
*/
Creeper::Creeper(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	vX_ = ( (std::rand()%16)/8 + .15 ) * ( (std::rand()%2)*2-1 );
	vY_ = ( (std::rand()%16)/8 + .15 ) * ( (std::rand()%2)*2-1 );
	//      ^random value from .15 to 2.15   ^randomly switches to negative
}

/** 
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
