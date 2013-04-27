#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

// For trig calculations and rand
#include <cmath>
const double PI = 3.14159265;

class GameSpace; // so that we can use a pointer to the GameSpace for the parent

/** This is an abstract base class for enemies, items, and the player.
*/
class Thing : public QGraphicsPixmapItem
{
	//Q_OBJECT
	
	public: // member functions
		Thing(QPixmap& picture, GameSpace* parent, Thing* player); // constructor that takes in a pointer to the parent
		~Thing();
		
		// Modifiers
		void setPos(double x, double y);
		/** Each Thing should specify how to move based on this function; they should set xPrecise_ and yPrecise_ so that the Thing will be moved when the timer triggers. */
		virtual void updatePrecisePos(int windowMaxX, int windowMaxY) =0;
		void move();
	
	protected:
		// Data members
			/** pointer to the GameSpace this thing is in */
			GameSpace* parent_;
			/** x position to move to when the timer updates (this is here so we can use movement at less than 1 pixel per timer without slowing timer) */
			double xPrecise_;
			/** y position to move to when the timer updates */
			double yPrecise_;
			/** pointer to the player, used in enemies' movement */
			Thing* player_;
};



#endif // THING_H
