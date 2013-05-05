#include "enemies.h"



/** Constructor. Calls Thing constructor and sets speed limit, angle change, and angle change's initial direction.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item, used for motion
*/
Skeleton::Skeleton(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	speedLimit_ = 8.0;
	angleChange_ = PI/2.0 + PI/180.0;
	if(rand()%2) angleChange_ = -angleChange_;
}

/** Moves skeleton. Skeletons circle the player, moving very slightly away.
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Skeleton::updatePrecisePos(const int& windowMaxX, const int& windowMaxY)
{
	// Find the difference between the skeleton's and the player's positions
	double deltaX = player_->x() - x(),
	       deltaY = player_->y() - y();
	
	// Set the radius to move
	double r = std::sqrt(std::abs(deltaX*deltaX + deltaY*deltaY))/400.0 + 2.0;
	
	// Set the angle theta at which the skeleton will move for this frame
	double th;
	if(deltaX == 0) {th = PI/2.0;} // make sure we don't divide by zero
	else {th = std::atan(deltaY/deltaX);}
	// Check whether or not to move in the opposite direction (because atan() only works from -PI to PI)
	if(deltaX < 0) th += PI;
	// Set the angle so the skeleton circles the player.
	if(rand()%960 == 0) angleChange_ = -angleChange_;
	th += angleChange_;
	
	// Move the skeleton by r if it is less than the speed limit and 
	if(r > speedLimit_) r = speedLimit_;
	xPrecise_ += r * std::cos(th);
	yPrecise_ += r * std::sin(th);
	
	// Make sure player does not go offscreen (no bounce)
	checkEdgesSlide(windowMaxX, windowMaxY);
}
