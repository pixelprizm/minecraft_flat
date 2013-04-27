#include "steve.h"



Steve::Steve(QPixmap& picture, GameSpace* parent)
:
	Thing(picture, parent, NULL)
{
	health_ = 10;
	moveToX_ = 400;
	moveToY_ = 300;
	speedLimit_ = .2;
	setOffset(-pixmap().width()/2, -pixmap().height()/2);
}

/** 
*/
void Steve::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	double deltaX = moveToX_ - x(),
	       deltaY = moveToY_ - y();
	
	double r = std::sqrt(std::abs(deltaX*deltaX + deltaY*deltaY)); // distance to move
	
	// Set the angle at which the player will move for this frame
	double th;
	if(deltaX == 0) {th = PI/2;} // make sure we don't divide by zero
	else {th = std::atan(deltaY/deltaX);}
	// Check whether or not to move in the opposite direction (because atan() only works from -PI to PI)
	if(deltaX < 0)
	{
		th += PI;
	}
	
	// Move the player by r if it is less than the speed limit and 
	if(r > speedLimit_) r = speedLimit_;
	xPrecise_ += r * std::cos(th);
	yPrecise_ += r * std::sin(th);
	
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	// Make sure player does not go offscreen
	if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ = 0          + halfWidth;  }
		// left
	if(yPrecise_ - halfHeight < 0         ) { yPrecise_ = 0          + halfHeight; }
		// top
	if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ = windowMaxX - halfWidth;  }
		// right
	if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ = windowMaxY - halfHeight; }
		// bottom
	
	/*
	if(deltaX < speedLimit_) {xPrecise_ += deltaX;}
	else {xPrecise_ += speedLimit_;}
	if(deltaY < speedLimit_) {yPrecise_ += deltaY;}
	else {yPrecise_ += speedLimit_;}
	
	if(x() < moveToX_)
	{
		xPrecise_ += .5;
	}
	else if(x() > moveToX_)
	{
		xPrecise_ -= .5;
	}
	if(y() < moveToY_)
	{
		yPrecise_ += .5;
	}
	else if(y() > moveToY_)
	{
		yPrecise_ -= .5;
	}*/
	//show();
}

/** Sets the Thing's target coordinates to move to.
*/
void Steve::moveTo(double x, double y) { moveToX_ = x; moveToY_ = y; }
