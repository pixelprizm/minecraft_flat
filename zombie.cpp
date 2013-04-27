#include "enemies.h"



Zombie::Zombie(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	speedLimit_ = .2;
	setOffset(-pixmap().width()/2, -pixmap().height()/2);
}

/** Move the zombie toward the player. Same as Steve::updatePrecisePos() except it moves toward the player, not the cursor
*/
void Zombie::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	double deltaX = player_->x() - x(),
	       deltaY = player_->y() - y();
	
	// Set the angle at which the player will move for this frame
	double th;
	if(deltaX == 0) {th = PI/2;} // make sure we don't divide by zero
	else {th = std::atan(deltaY/deltaX);}
	// Check whether or not to move in the opposite direction (because atan() only works from -PI to PI)
	if(deltaX < 0)
	{
		th += PI;
	}
	
	// Move the zombie toward the player at the speedlimit
	xPrecise_ += speedLimit_ * std::cos(th);
	yPrecise_ += speedLimit_ * std::sin(th);
	
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	// Make sure zombie does not go offscreen
	if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ = 0          + halfWidth;  }
		// left
	if(yPrecise_ - halfHeight < 0         ) { yPrecise_ = 0          + halfHeight; }
		// top
	if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ = windowMaxX - halfWidth;  }
		// right
	if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ = windowMaxY - halfHeight; }
		// bottom
}
