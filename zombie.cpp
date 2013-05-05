#include "enemies.h"



/** Constructor. Calls Thing constructor and sets max speed.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item, used by some enemies for motion
*/
Zombie::Zombie(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	speed_ = .6;
}

/** Update zombie's position. The zombie moves toward the player. Same as Steve::updatePrecisePos() except it moves toward the player, not the cursor
* @param windowMaxX the width of the area valid for motion
* @param windowMaxY the height of the area valid for motion
*/
void Zombie::updatePrecisePos(const int& windowMaxX, const int& windowMaxY)
{
	double deltaX = player_->x() - x(),
	       deltaY = player_->y() - y();
	
	// Set the angle theta at which the zombie will move for this frame
	double th;
	if(deltaX == 0) {th = PI/2;} // make sure we don't divide by zero
	else {th = std::atan(deltaY/deltaX);}
	// Check whether or not to move in the opposite direction (because atan() only works from -PI to PI)
	if(deltaX < 0) th += PI;
	
	// Move the zombie toward the player at the speedlimit
	xPrecise_ += speed_ * std::cos(th);
	yPrecise_ += speed_ * std::sin(th);
	
	// Make sure zombie does not go offscreen (no bounce)
	checkEdgesSlide(windowMaxX, windowMaxY);
}
