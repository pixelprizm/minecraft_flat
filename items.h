#ifndef ITEMS_H
#define ITEMS_H

#include "thing.h"

/** Heart item. Basically just a picture; collisions are detected and handled externally. Does not move.
*/
class Heart : public Thing
{
	public:
		Heart(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int, int);
};

#endif // ITEMS_H
