#include "thing.h"
#include "gamespace.h"

/** Constructor.
* @param parent Pointer to the GameSpace that holds this item.
*/
Thing::Thing(GameSpace* parent)
//:
//	QGraphicsPixmapItem(parent->scene())
{
	parent_ = parent;
	health_ = 10;
	vX = 0;
	vY = 0;
}

/** Destructor for thing
*/
Thing::~Thing()
{
	// parent->scene_->removeItem(this);
}
