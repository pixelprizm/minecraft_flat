// Copyright (C) 2013 Eric Gauderman



#include "thing.h"
#include "gamespace.h"



/** Constructor. Calls the constructor for QGraphicsPixmapItem and initializes values.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item, used by some enemies for motion
*/
Thing::Thing(QPixmap& picture, GameSpace* parent, Thing* player)
:
	QGraphicsPixmapItem(picture)
{
	parent_ = parent;
	player_ = player;
	xPrecise_ = x();
	yPrecise_ = y();
	setOffset(-pixmap().width()/2, -pixmap().height()/2); // sets this thing's position to its center
}

/** Destructor. Removes the Thing from the scene
*/
Thing::~Thing()
{
	parent_->scene()->removeItem(this);
}

/** Sets the Thing to a random position within the confines of the gamespace
* @param windowMaxX Gamespace's width
* @param windowMaxY Gamespace's height
*/
void Thing::randomPos(const int& windowMaxX, const int& windowMaxY)
{
	setPos
	(
		rand()%(windowMaxX - pixmap().width() ) + (pixmap().width()  / 2),
		rand()%(windowMaxY - pixmap().height()) + (pixmap().height() / 2)
	); //       ^rand range                         ^accounts for offset
}

/** overrides (and internally calls) QGraphicsPixmapItem::setPos() to maintain consistency with the x_ and y_ members.
* @param x The desired new x-position
* @param y The desired new y-position
*/
void Thing::setPos(double x, double y)
{ xPrecise_ = x; yPrecise_ = y; QGraphicsPixmapItem::setPos(x,y); }

/** This is called on every timer pulse and simply moves the character's position to the specified values of xPrecise_ and yPrecise_
*/
void Thing::move()
{
	QGraphicsPixmapItem::setPos(xPrecise_,yPrecise_);
}



// ===========================================================================================
// -------------------------------- HELPER FUNCTIONS -----------------------------------------
// ===========================================================================================

/** Used by Things to check collision with screen edges.  Thing will bounce off of edges and move in opposite direction.  Requires Thing to have and track an X and Y velocity
* @param windowMaxX Width of the gamespace
* @param windowMaxY Height of the gamespace
* @param vX Reference to the Thing's x-velocity, to set it in the opposite direction in the event of a bounce
* @param vY Reference to the Thing's y-velocity, to set it in the opposite direction in the event of a bounce
*/
void Thing::checkEdgesBounce(const int& windowMaxX, const int& windowMaxY, double& vX, double& vY)
{
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	if(xPrecise_ - halfWidth  < 0         ) { vX = -vX; xPrecise_+=vX; } // left
	if(yPrecise_ - halfHeight < 0         ) { vY = -vY; yPrecise_+=vY; } // top
	if(xPrecise_ + halfWidth  > windowMaxX) { vX = -vX; xPrecise_+=vX; } // right
	if(yPrecise_ + halfHeight > windowMaxY) { vY = -vY; yPrecise_+=vY; } // bottom
}

/** Used by Things to check collision with screen edges.  Thing will slide against edges, not bouncing off.
* @param windowMaxX Width of the gamespace
* @param windowMaxY Height of the gamespace
*/
void Thing::checkEdgesSlide(const int& windowMaxX, const int& windowMaxY)
{
	int halfWidth = pixmap().width()/2;
	int halfHeight = pixmap().height()/2;
	if(xPrecise_ - halfWidth  < 0         ) { xPrecise_ = 0          + halfWidth;  } // left
	if(yPrecise_ - halfHeight < 0         ) { yPrecise_ = 0          + halfHeight; } // top
	if(xPrecise_ + halfWidth  > windowMaxX) { xPrecise_ = windowMaxX - halfWidth;  } // right
	if(yPrecise_ + halfHeight > windowMaxY) { yPrecise_ = windowMaxY - halfHeight; } // bottom
}
