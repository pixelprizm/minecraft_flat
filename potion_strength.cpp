#include "items.h"



/** Constructor. Calls Thing constructor.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item
*/
PotionStrength::PotionStrength(QPixmap& picture, GameSpace* parent, Steve* player)
:
	Item(picture, parent, player)
{
	speed_ = 1;
	angle_ = ((std::rand()%48)/48.0)*(2.0*PI); // initialize angle_ to a random direction
}

/** Slowly moves the potion in a small circle
*/
void PotionStrength::updatePrecisePos(const int& windowMaxX, const int& windowMaxY)
{
	// Update position
	xPrecise_ += speed_ * std::cos(angle_);
	yPrecise_ += speed_ * std::sin(angle_);
	
	// Update angle so that it continues motion in a circle
	angle_ += (1.0/48.0)*(2.0*PI);
	
	// Make sure potion does not move off screen (no bounce)
	checkEdgesSlide(windowMaxX, windowMaxY);
}

/** Strength potion's effect on the player--increase 
*/
void PotionStrength::playerEffect()
{
	stevePlayer_->invincible() += 30;
}
