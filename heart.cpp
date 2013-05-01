#include "items.h"



/** Constructor. Calls Thing constructor.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item
*/
Heart::Heart(QPixmap& picture, GameSpace* parent, Thing* player)
:
	Thing(picture, parent, player)
{
	
}

/** Empty function for updatePrecise Pos, because Heart does not move. Parameters are not used.
*/
void Heart::updatePrecisePos(int, int)
{
	
}
