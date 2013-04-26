#ifndef ITEMS_H
#define ITEMS_H

#include "thing.h"

/** Heart item
*/
class Heart : public Thing
{
	public:
		Heart(GameSpace* parent);
		void update();
	
	private: // data members
};

#endif // ITEMS_H
