#ifndef ITEMS_H
#define ITEMS_H

#include "thing.h"
#include "steve.h"



/** Item abstract base class. Requires items to have the function playerEffect.
*/
class Item : public Thing
{
	public:
		/** Constructor; just calls Thing constructor */
		Item(QPixmap& picture, GameSpace* parent, Steve* player) : Thing(picture, parent, player) { stevePlayer_ = player; }
		/** Empty function. Items will override it if they move. */
		virtual void updatePrecisePos(const int&, const int&) { }
		/** The effect each item does on the player */
		virtual void playerEffect() =0;
	
	protected: // Data Members
		/** player pointer which is specifically a Steve pointer, so that we can use public functions that only exist in Steve */
		Steve* stevePlayer_;
};



/** Heart item. Basically just a picture; collisions are detected and handled externally. Does not move.
*/
class Heart : public Item
{
	public:
		Heart(QPixmap& picture, GameSpace* parent, Steve* player);
		void playerEffect();
};



/** Strength potion. Makes the player invincible for a limited amount of time.
*/
class PotionStrength : public Item
{
	public:
		PotionStrength(QPixmap& picture, GameSpace* parent, Steve* player);
		void updatePrecisePos(const int&, const int&);
		void playerEffect();
	private:
		/** Speed at which the potion will move */
		double speed_;
		/** Angle for the potion to move next */
		double angle_;
};



#endif // ITEMS_H
