#ifndef ENEMIES_H
#define ENEMIES_H

#include "thing.h"

/** Zombie enemy
*/
class Zombie : public Thing
{
	public: // member functions
		Zombie(GameSpace* parent);
		void update();
	
	private: // data members
};

/** Spider enemy
*/
class Spider : public Thing
{
	public: // member functions
		Spider(GameSpace* parent);
		void update();
	
	private: // data members
};

/** Creeper enemy
*/
class Creeper : public Thing
{
	public: // member functions
		Creeper(GameSpace* parent);
		void update();
	
	private: // data members
};

/** Skeleton enemy
*/
class Skeleton : public Thing
{
	public: // member functions
		Skeleton(GameSpace* parent);
		void update();
	
	private: // data members
};

/** Enderman enemy
*/
class Enderman : public Thing
{
	public: // member functions
		Enderman(GameSpace* parent);
		void update();
	
	private: // data members
};



#endif // ENEMIES_H
