#include "thing.h"

class GameSpace; // so that we can use a parent pointer

/** Main character class
*/
class Steve : public Thing
{
	public: // Member functions
		Steve(GameSpace* parent);
		void update();
	
	private: // data members
};
