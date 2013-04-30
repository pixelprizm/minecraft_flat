#ifndef ENEMIES_H
#define ENEMIES_H

#include "thing.h"



/** Zombie enemy
*/
class Zombie : public Thing
{
	public: // member functions
		Zombie(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
		double speedLimit_;
};



/** Spider enemy
*/
class Spider : public Thing
{
	public: // member functions
		Spider(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
		double vX_;
		double vY_;
		void randomizeVel();
};



/** Creeper enemy
*/
class Creeper : public Thing
{
	public: // member functions
		Creeper(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
		double vX_;
		double vY_;
};



/** Skeleton enemy
*/
class Skeleton : public Thing
{
	public: // member functions
		Skeleton(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
		double speedLimit_;
		double angleChange_;
};



/** Enderman enemy
*/
class Enderman : public Thing
{
	public: // member functions
		Enderman(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
};



#endif // ENEMIES_H
