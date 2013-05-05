#include "items.h"



/** Constructor. Calls Thing constructor.
* @param picture The picture for this to display
* @param parent Pointer to the GameSpace that holds this item.
* @param player Pointer to the player item
*/
Heart::Heart(QPixmap& picture, GameSpace* parent, Steve* player)
:
	Item(picture, parent, player)
{
	
}

/** Heart's effect on the player--increase player's health by 1
*/
void Heart::playerEffect()
{
	stevePlayer_->changeHealth(+1);
}
