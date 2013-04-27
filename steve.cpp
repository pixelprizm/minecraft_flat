#include "steve.h"

Steve::Steve(QPixmap& picture, GameSpace* parent)
:
	Thing(picture, parent, NULL)
{
	
}

/** 
*/
void Steve::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	if(x() < moveToX_)
	{
		xPrecise_ += 1;
	}
	else if(x() > moveToX_)
	{
		xPrecise_ -= 1;
	}
	if(y() < moveToY_)
	{
		yPrecise_ += 1;
	}
	else if(y() > moveToY_)
	{
		yPrecise_ -= 1;
	}
}

/** Sets the Thing's target coordinates to move to.
*/
void Steve::moveTo(double x, double y) { moveToX_ = x; moveToY_ = y; }
