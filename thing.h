// Copyright (C) 2013 Eric Gauderman



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
	public: // member functions
		Thing(QPixmap& picture, GameSpace* parent, Thing* player); // constructor that takes in a pointer to the parent
		~Thing();
		
		// Modifiers
		/** Each Thing should specify how to move based on this function; they should set xPrecise_ and yPrecise_ so that the Thing will be moved when the timer triggers. */
		virtual void updatePrecisePos(const int& windowMaxX, const int& windowMaxY) =0;
		void setPos(double x, double y);
		void move();
		void randomPos(const int& windowMaxX, const int& windowMaxY);
		
		// Accessors
		/** Return a pointer to this Thing's parent GameSpace */
		GameSpace* parent() { return parent_; }
	
	protected: // Data members
		/** pointer to the GameSpace this thing is in */
		GameSpace* parent_;
		/** x position to move to when the timer updates (these are here so we can use movement at less than 1 pixel per timer without slowing timer) */
		double xPrecise_;
		/** y position to move to when the timer updates */
		double yPrecise_;
		/** pointer to the player, used in enemies' movement */
		Thing* player_;
	
	protected: // Helper Functions
		void checkEdgesBounce(const int& windowMaxX, const int& windowMaxY, double& vX, double& vY);
		void checkEdgesSlide(const int& windowMaxX, const int& windowMaxY);
};



#endif // THING_H
