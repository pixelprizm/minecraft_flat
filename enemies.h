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
		/** Speed at which the zombie travels */
		double speed_;
};



/** Spider enemy
*/
class Spider : public Thing
{
	public: // member functions
		Spider(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // helper functions
		void randomizeVel();
	
	private: // data members
		/** x-velocity */
		double vX_;
		/** y-velocity */
		double vY_;
};



/** Creeper enemy
*/
class Creeper : public Thing
{
	public: // member functions
		Creeper(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
	
	private: // data members
		/** x-velocity */
		double vX_;
		/** y-velocity */
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
		/** The skeleton's maximum speed */
		double speedLimit_;
		/** The angle to add to the skeleton's direction. Used to make the skeleton circle the player. */
		double angleChange_;
};



/** Enderman enemy
*/
class Enderman : public Thing
{
	public: // member functions
		Enderman(QPixmap& picture, GameSpace* parent, Thing* player);
		void updatePrecisePos(int windowMaxX, int windowMaxY);
};



#endif // ENEMIES_H
