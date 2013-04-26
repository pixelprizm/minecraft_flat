#ifndef THING_H
#define THING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class GameSpace; // so that we can use a pointer to the GameSpace for the scene

/** This is an abstract base class for enemies, items, and the player.
*/
class Thing : public QGraphicsPixmapItem
{
	//Q_OBJECT
	
	public: // member functions
		Thing(GameSpace* parent); // constructor that takes in a pointer to the parent
		~Thing();
		
		/** This is to be called every timer and implemented differently for each thing.
		*     Each enemy should handle moving and attacking with this function; items can simply hold still if needed.
		*/
		virtual void update() =0;
	
	protected: // data members
		/** enemy's current health, unused for items */
		int health_;
		/** pointer to the GameSpace this thing is in */
		GameSpace* parent_;
		/** x velocity (possibly unused by items) */
		double vX;
		/** y velocity (possibly unused by items) */
		double vY;
};



#endif // THING_H
