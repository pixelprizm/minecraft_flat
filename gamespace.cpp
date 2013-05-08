#include "gamespace.h"
#include "mainwindow.h"
#include <ctime> // for rand seed



/** Constructor. Loads pictures, builds the game area, and initializes flag values
* @param parent Pointer to the parent MainWindow. This is passed to QGraphicsView
*/
GameSpace::GameSpace(MainWindow* parent)
:
	QGraphicsView(parent)
{
	parent_ = parent;
	
	// Initialize scene
	scene_ = new QGraphicsScene;
	setScene(scene_);
	
	// Create the background (important that this is the first image added to the scene)
	backgroundPics_.push_back(new QPixmap("images/dirt_background_800.png")); // 0 (theoretically, a title screen)
	backgroundPics_.push_back(new QPixmap("images/dirt_background_800.png")); // 1
	backgroundPics_.push_back(new QPixmap("images/netherBrick_background_800.png")); // 2
	backgroundPics_.push_back(new QPixmap("images/whiteStone_background_800.png")); // 3
	backgroundPicItem_ = new QGraphicsPixmapItem(*backgroundPics_[0]);
	scene_->addItem(backgroundPicItem_);
	backgroundPicItem_->setZValue(-1);
	
	// Initialize player
	stevePic_ = new QPixmap("images/steve.png");
	player_ = NULL; // we will initialize Steve in the first game
	
	// Initialize pixmaps for enemies
	zombiePic_ = new QPixmap("images/zombie.png");
	spiderPic_ = new QPixmap("images/spider.png");
	creeperPic_ = new QPixmap("images/creeper.png");
	skeletonPic_ = new QPixmap("images/skeleton.png");
	endermanPic_ = new QPixmap("images/enderman.png");
	
	// Initialize item pixmaps
	heartPic_ = new QPixmap("images/heart.png");
	potionStrengthPic_ = new QPixmap("images/potion_strength.png");
	
	// Initialize timer
	timer_ = new QTimer(this);
	timer_->setInterval(1); // this is kept low so that the player's update speed is fast and so we have specific control over the speed of all game events
	connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	// Enable mouse capture
	setMouseTracking(true);
	setFocus();
	
	// Initialize score
	score_ = 0;
	
	// Initialize level
	level_ = 0; // because we haven't started a game yet
	
	// Initialize game status flags
	gameInProgress_ = false;
	gameOverFlag_ = false;
}

/** Destructor. Deletes all enemies, items, and the player. They remove themselves from the scene.
*/
GameSpace::~GameSpace()
{
	timer_->stop();
	if(gameInProgress_)
	{
		while(!enemies_.empty())
		{
			delete enemies_.back();
			enemies_.pop_back();
		}
		while(!items_.empty())
		{
			delete items_.back();
			items_.pop_back();
		}
	}
	delete player_;
}



// ============================================================================
// ---------------------------------- MODIFIERS -------------------------------
// ============================================================================

/** Helper function to initialize the values of the game.  This is called whenever a level begins or the game restarts.
*/
void GameSpace::initialize()
{
	// First, initialize the player
		if(player_) {delete player_;} // get rid of old player so we create a new one, correctly initialized
		player_ = new Steve(*stevePic_, this);
		player_->setPos(width()/2,height()/2);
		scene_->addItem(player_);
	// Then, get rid of any enemies and items
		while(!enemies_.empty())
		{
			delete enemies_.back();
			enemies_.pop_back();
		}
		while(!items_.empty())
		{
			delete items_.back();
			items_.pop_back();
		}
	
	// Initialize values used in controlling speed of the game
		timerCount_ = 1; // it's 1 so that items & enemies don't spawn instantly
		period_ = 28;
		periodCount_ = 1; // it's 1 so that items & enemies don't spawn instantly
	
	// Initialize score
		score_ = 0;
}

/** Start a new game at the passed-in level.
* @param maintainGame Whether or not to keep game Things and score
* @param level The level to start the game at
*/
void GameSpace::startLevel(bool maintainGame, int level)
{
	level_ = level;
	startLevel(maintainGame);
}

/** Start a new game at the current level number. First deletes old data, then creates and initializes new data
* @param maintainGame Whether or not to keep game Things and score
*/
void GameSpace::startLevel(bool maintainGame)
{
	// Stop the timer in case a game had already started
	timer_->stop();
	
	// Initialize the game if desired
	if(!maintainGame) initialize();
	timerCount_ = 1;
	periodCount_ = 1;
	
	// Change the background to the one for this level
	scene_->removeItem(backgroundPicItem_);
	delete backgroundPicItem_;
	backgroundPicItem_ = new QGraphicsPixmapItem(*backgroundPics_[level_]);
	scene_->addItem(backgroundPicItem_);
	backgroundPicItem_->setZValue(-1);
	
	// Set game status flags
	gameOverFlag_ = false;
	gameInProgress_ = true;
	
	// Update MainWindow's labels (note: they're blank unless gameInProgress_ to be true)
	parent_->updateLabels();
	
	// Start the game!
	timer_->start();
}

/** Freeze or resume gameplay.
* @param pause If true, pause the game; if false, resume the game
*/
void GameSpace::pauseGame(bool pause)
{
	if(pause) { timer_->stop(); }
	else { timer_->start(); }
}

/** Called when the mouse is moved. Updates Steve's target location.
* @param event Data for the mouse event (used for location)
*/
void GameSpace::mouseMoveEvent(QMouseEvent* event)
{
	if(!(timer_->isActive())) return;
	
	player_->moveTo(event->pos().x(), event->pos().y());
}



// ============================================================================
// ---------------------------------- SLOTS -----------------------------------
// ============================================================================

/** Called whenever the timer goes off. Handles animation and triggers Things' functions for motion
*/
void GameSpace::handleTimer()
{
	// Update the player's position, independent of period_; also makes player movement very smooth
	player_->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
	player_->move();
	
	// If player is invincible, update invincibility
	if(timerCount_ % 300 == 0 && player_->invincible()) { player_->invincible()--; }
		
	// Add a new strength potion every number of periods below
	if(timerCount_ % 20000 == 0 && level_ > 1)
	{
		Item* newItem = new PotionStrength(*potionStrengthPic_, this, player_);
		// Initialize the potion's position, add it to items list, add it to the scene
		newItem->randomPos(WINDOW_MAX_X, WINDOW_MAX_Y);
		items_.push_back(newItem);
		scene_->addItem(newItem);
	}
		
	// Check if new level is reached
	if( (timerCount_%(50000+30000*level_) == 0) && (level_ < 3)) { startLevel(true, level_+1); return; }
	
	if(timerCount_ % period_ == 0)
	{
		// ------------------- ADD NEW THINGS ----------------------
			// Add a new enemy every specified number of periods
			if(periodCount_ % 63 == 0)
			{
				Thing* newEnemy = NULL;
				switch(rand()%(level_+2))
				{
					case 0: newEnemy = new Zombie(*zombiePic_, this, player_);
						break;
					case 1: newEnemy = new Spider(*spiderPic_, this, player_);
						break;
					case 2: newEnemy = new Creeper(*creeperPic_, this, player_);
						break;
					case 3: newEnemy = new Skeleton(*skeletonPic_, this, player_);
						break;
					case 4: newEnemy = new Enderman(*endermanPic_, this, player_);
						break;
				}
				// Initialize the enemy's position
				newEnemy->randomPos(WINDOW_MAX_X, WINDOW_MAX_Y);
				// Add the enemy to the list of enemies and to the scene
				enemies_.push_back(newEnemy);
				scene_->addItem(newEnemy);
			}
			// Add a new heart every number of periods below
			if(periodCount_ % 376 == 0)
			{
				Item* newItem = new Heart(*heartPic_, this, player_);
				// Initialize the heart's position, add it to vector, add it to the scene
				newItem->randomPos(WINDOW_MAX_X, WINDOW_MAX_Y);
				items_.push_back(newItem);
				scene_->addItem(newItem);
			}
		
		// ------------------------ UPDATE THINGS ---------------------------------
			// Update each item & check for collisions between items and the player
			for(unsigned int i = 0; i < items_.size(); i++)
			{
				// Move the item (hearts don't move, potions do)
				items_[i]->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
				items_[i]->move();
			
				if(items_[i]->collidesWithItem(player_))
				{
					items_[i]->playerEffect();
					score_+=100;
					delete items_[i]; // remove from scene & delete data
					items_.erase(items_.begin()+i); // remove pointer form vector
				}
			}
			// Update each enemy & check for collisions
			for(unsigned int i = 0; i < enemies_.size(); i++)
			{
				enemies_[i]->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
				enemies_[i]->move();
			
				if(enemies_[i]->collidesWithItem(player_))
				{
					delete enemies_[i]; // remove from scene & delete data
					enemies_.erase(enemies_.begin()+i); // remove pointer form vector
					if(player_->invincible()==0) player_->changeHealth(-1); // if player is not invincible, give him damage
					if(gameOverFlag_) return; // in case a game ends when the player's health changes, stop trying to detect collisions
				}
			}
		
		// Update score
		if(periodCount_ % 4 == 0 && !gameOverFlag_) score_++;
		
		// Update MainWindow's labels
		parent_->updateLabels();
		
		// Increase period count
		periodCount_++;
	}
		
	// Every certain number of timer pulses, speed up the game by decreasing the period (does not affect player's speed)
	if(timerCount_ % 18000 == 0 && period_ > 8) period_--;
	
	timerCount_++;
}
