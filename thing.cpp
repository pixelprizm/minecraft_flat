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

/** overrides (and internally calls) QGraphicsPixmapItem::setPos() to maintain consistency with the x_ and y_ members.
*	@param x The desired new x-position
*	@param y The desired new y-position
*/
void Thing::setPos(double x, double y)
{ xPrecise_ = x; yPrecise_ = y; QGraphicsPixmapItem::setPos(x,y); }

/** This is called on every timer pulse and simply moves the character's position to the specified values of xPrecise_ and yPrecise_
*/
void Thing::move()
{
	QGraphicsPixmapItem::setPos(xPrecise_,yPrecise_);
}
