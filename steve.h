#ifndef STEVE_H
#define STEVE_H

#include "thing.h"

/** Main character class
*/
class Steve : public Thing
{
	public: // Member functions
		Steve(QPixmap& picture, GameSpace* parent);
		
		// Modifiers
		void updatePrecisePos(int windowMaxX, int windowMaxY);
		void moveTo(double x, double Y);
		void takeDamage(int damage);
		
		// Accessors
		/** Return the number of lives left */
		int lives() { return lives_; }
	
	private: // data members
		int moveToX_;
		int moveToY_;
		double speedLimit_;
		/** current number of lives */
		int lives_;
};

#endif // STEVE_H
