#include "steve.h"
#include "mainwindow.h"
#include "gamespace.h" // for use of parent pointer



/** 
*/
Steve::Steve(QPixmap& picture, GameSpace* parent)
:
	Thing(picture, parent, NULL)
{
	lives_ = 10;
	moveToX_ = 400;
	moveToY_ = 300;
	speedLimit_ = .2;
}

/** Called every clock pulse.  Player moves toward the cursor with a limited speed; player slows down when close to pointer.
* @param windowMaxX Sets the maximum x-position of the player
* @param windowMaxY Sets the maximum y-position of the player
*/
void Steve::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	// Find the difference between the player's position and the desired position
	double deltaX = (moveToX_ - x()),
	       deltaY = (moveToY_ - y());
	
	// Set the radius to move
	double r = std::sqrt(deltaX*deltaX + deltaY*deltaY)/160;
	
	// Set the angle theta at which the player will move for this frame
	double th;
	if(deltaX == 0) {th = PI/2;} // make sure we don't divide by zero
	else {th = std::atan(deltaY/deltaX);}
	// Check whether or not to move in the opposite direction (because atan() only works from -PI to PI)
	if(deltaX < 0) th += PI;
	
	// Move the player by r if it is less than the speed limit and 
	if(r > speedLimit_) r = speedLimit_;
	xPrecise_ += r * std::cos(th);
	yPrecise_ += r * std::sin(th);
	
	// Make sure player does not go offscreen
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ = 0          + halfWidth;  } // left
	if(yPrecise_ - halfHeight < 0         ) { yPrecise_ = 0          + halfHeight; } // top
	if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ = windowMaxX - halfWidth;  } // right
	if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ = windowMaxY - halfHeight; } // bottom
}

/** Sets the Thing's target coordinates to move to.
*/
void Steve::moveTo(double x, double y) { moveToX_ = x; moveToY_ = y; }

/** Deals the passed-in amount of damage to the player
*/
void Steve::changeHealth(int delta)
{
	lives_ += delta;
	parent()->parent()->healthUI->setText(QString::number(lives_));
	if(lives_ <= 0) parent()->parent()->gameOver();
}
