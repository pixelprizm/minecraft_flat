#include "enemies.h"



/** 
*/
Creeper::Creeper(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	vX_ = ( (rand()%10)/20 + .3 ) * ( (-1)^(rand()%2) );
	vY_ = ( (rand()%10)/20 + .3 ) * ( (-1)^(rand()%2) );
}

/** 
*/
void Creeper::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	xPrecise_ += vX_;
	yPrecise_ += vY_;
	if(xPrecise_<0) { vX_ = -vX_; xPrecise_+=vX_; }
	if(yPrecise_<0) { vY_ = -vY_; yPrecise_+=vY_; }
	if(xPrecise_+pixmap().width()  > windowMaxX) { vX_ = -vX_; xPrecise_+=vX_; }
	if(yPrecise_+pixmap().height() > windowMaxY) { vY_ = -vY_; yPrecise_+=vY_; }
}
