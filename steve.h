#ifndef STEVE_H
#define STEVE_H

#include "thing.h"

/** Main character class.
*/
class Steve : public Thing
{
	public: // Member functions
		Steve(QPixmap& picture, GameSpace* parent);
		
		// Modifiers
		void updatePrecisePos(const int& windowMaxX, const int& windowMaxY);
		void moveTo(double x, double y);
		void changeHealth(int delta);
		
		// Accessors
		/** Health accessor */
		int health() { return health_; }
		/** Remaining Invincibility accessor (reference) */
		int& invincible() { return invincible_; }
	
	private: // data members
		/** the x-position for the player to move to, i.e., the position of the mouse cursor */
		int moveToX_;
		/** the y-position for the player to move to, i.e., the position of the mouse cursor */
		int moveToY_;
		/** maximum speed at which the player can travel in any direction */
		double speedLimit_;
		/** current number of lives */
		int health_;
		/** how long the player will remain invincible (in periods) */
		int invincible_;
};

#endif // STEVE_H
