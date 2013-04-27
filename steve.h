#ifndef STEVE_H
#define STEVE_H

#include "thing.h"

/** Main character class
*/
class Steve : public Thing
{
	public: // Member functions
		Steve(QPixmap& picture, GameSpace* parent);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
		// Helper functions
		void moveTo(double x, double Y);
	
	private: // data members
		int moveToX_;
		int moveToY_;
		double speedLimit_;
		/** current health */
		int health_;
};

#endif // STEVE_H
