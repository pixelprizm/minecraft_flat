#include "thing.h"
#include "gamespace.h"



/** Constructor.
* @param parent Pointer to the GameSpace that holds this item.
*/
Thing::Thing(QPixmap& picture, GameSpace* parent, Thing* player)
:
	QGraphicsPixmapItem(picture)
{
	parent_ = parent;
	player_ = player;
	xPrecise_ = x();
	yPrecise_ = y();
}

/** Destructor for thing
*/
Thing::~Thing()
{
	parent_->scene()->removeItem(this);
}

/** overrides (and internally calls) QGraphicsPixmapItem::setPos() to enable this Thing's x_ and y_ members.
*/
void Thing::setPos(double x, double y) { xPrecise_ = x; yPrecise_ = y; QGraphicsPixmapItem::setPos(x,y); }

/** This is called on every timer and simply moves the character's position to the specified values of xPrecise_ and yPrecise_
*/
void Thing::move()
{
	QGraphicsPixmapItem::setPos(xPrecise_,yPrecise_);
}
