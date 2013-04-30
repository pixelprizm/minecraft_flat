#include "items.h"



/** 
*/
Heart::Heart(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	setOffset(-pixmap().width()/2, -pixmap().height()/2); // sets this thing's position to its center
}

/** 
*/
void Heart::updatePrecisePos(int windowMaxX, int windowMaxY)
{
	
}
