#ifndef ITEMS_H
#define ITEMS_H

#include "thing.h"

/** Heart item
*/
class Heart : public Thing
{
	public:
		Heart(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
};

#endif // ITEMS_H
