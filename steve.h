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
		void updatePrecisePos(int windowMaxX, int windowMaxY);
		void moveTo(double x, double y);
		void changeHealth(int delta);
		
		// Accessors
		/** Health accessor
		*	@return Number of lives left
		*/
		int health() { return health_; }
	
	private: // data members
		/** the x-position for the player to move to, i.e., the position of the mouse cursor */
		int moveToX_;
		/** the y-position for the player to move to, i.e., the position of the mouse cursor */
		int moveToY_;
		/** maximum speed at which the player can travel in any direction */
		double speedLimit_;
		/** current number of lives */
		int health_;
};

#endif // STEVE_H
