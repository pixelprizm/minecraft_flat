// Include a qpixmap or whatever

class gamespace; // so that we can use a pointer to the GameSpace

/** This is an abstract base class for enemies.
*/
class Enemy
{
	public: // member functions
		Enemy(GameSpace* parent); // constructor that takes in a pointer to the parent
		/** This is to be called every timer and implemented differently for each enemy.
		*     Each enemy should handle moving and attacking with this function.
		*/
		virtual void update() =0;
	
	protected: // data members
		int health_;
		GameSpace* parent_; // pointer to the GameSpace this thing is in
		// add a qpixmap or whatever here
};

/** Zombie enemy
*/
class Zombie : public Enemy
{
	public: // member functions
		void update();
	
	private: // data members
		
};

/** Creeper enemy
*/
class Creeper : public Enemy
{
	public: // member functions
		void update();
	
	private: // data members
		
};

/** Skeleton enemy
*/
class Skeleton : public Enemy
{
	public: // member functions
		void update();
	
	private: // data members
		
};

/** Spider enemy
*/
class Spider : public Enemy
{
	public: // member functions
		void update();
	
	private: // data members
		
};

/** Enderman enemy
*/
class Enderman : public Enemy
{
	public: // member functions
		void update();
	
	private: // data members
		
};
