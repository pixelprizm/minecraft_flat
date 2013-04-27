#include "gamespace.h"
#include "mainwindow.h"
#include <ctime> // for rand seed
#include <QMouseEvent>

//DEBUG
#include <iostream>
using namespace std;

/** Constructor. Loads pictures and builds the game area.
*/
GameSpace::GameSpace(MainWindow* parent)
:
	QGraphicsView(parent)
{
	gameInProgress_ = false;
	scene_ = new QGraphicsScene;
	setScene(scene_);
	
	// Create the background
	backgroundPic_ = new QPixmap("images/sand_background_800.png");
	backgroundPicItem_ = new QGraphicsPixmapItem(*backgroundPic_);
	scene_->addItem(backgroundPicItem_);
	
	player_ = NULL; // we will initialize Steve in the first game
	
	// Initialize pixmaps for Things, and seed random number
	srand(std::time(NULL));
	stevePic_ = new QPixmap("images/steve.png");
	zombiePic_ = new QPixmap("images/zombie.png");
	spiderPic_ = new QPixmap("images/spider.png");
	creeperPic_ = new QPixmap("images/creeper.png");
	skeletonPic_ = new QPixmap("images/skeleton.png");
	endermanPic_ = new QPixmap("images/enderman.png");
	heartPic_ = new QPixmap("images/heart.png");
	
	// Initialize timer
	timer_ = new QTimer(this);
	timer_->setInterval(1); // this is kept low so that the player's update speed is fast
	connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	// Initialize values used in controlling speed of the game
	timerCount_ = 0;
	period_ = 20;
	periodCount_ = 0;
	
	// Set mouse flags
	setMouseTracking(true);
	setFocus();
}

/** Destructor. Deletes all Things. They remove themselves from the scene.
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

/** Start a new game
*/
void GameSpace::startNewGame()
{
	timer_->stop();
	
	if(player_) delete player_; // get rid of old player so we create a new one, correctly initialized
	
	player_ = new Steve(*stevePic_, this);
	player_->setPos(400,300);
	//DEBUG
		cout << "Steve: " << player_->x() << " " << player_->y() << endl;

	scene_->addItem(player_);
	
	// If there was a previous game, get rid of the enemies (they remove themselves from the scene)
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
	//initialize Steve's position and health etc.
	gameInProgress_ = true;
	timer_->start();
}

void GameSpace::pauseGame(bool pause)
{
	if(pause) { timer_->stop(); }
	else { timer_->start(); }
}



/** Called when the mouse is moved. Updates Steve's location.
* @param event Data for the mouse event
*/
void GameSpace::mouseMoveEvent(QMouseEvent* event)//QGraphicsSceneMouseEvent* event)
{
	if(!(timer_->isActive())) return;
	
	player_->moveTo(event->pos().x(), event->pos().y());
}



// ============================================================================
// ---------------------------------- SLOTS -----------------------------------
// ============================================================================

/** Called whenever the timer goes off. Handles animation and triggers move functions
*/
void GameSpace::handleTimer()
{
	player_->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y); // these two lines keep the player updating at the speed of the timer, not limited by the period_ value
	player_->move();
	
	if(timerCount_ % period_ == 0)
	{
		// Add a new enemy every specified number of periods
		if(timerCount_ % 100 == 0)
		{
			Thing* newEnemy;
			int newWidth = 0, newHeight = 0;
			switch(rand()%5)
			{
				case 0: newEnemy = new Zombie(*zombiePic_, this, player_);
					newWidth = zombiePic_->width();
					newHeight = zombiePic_->height();
					break;
				case 1: newEnemy = new Spider(*spiderPic_, this, player_);
					newWidth = spiderPic_->width();
					newHeight = spiderPic_->height();
					break;
				case 2: newEnemy = new Creeper(*creeperPic_, this, player_);
					newWidth = creeperPic_->width();
					newHeight = creeperPic_->height();
					break;
				case 3: newEnemy = new Skeleton(*skeletonPic_, this, player_);
					newWidth = skeletonPic_->width();
					newHeight = skeletonPic_->height();
					break;
				case 4: newEnemy = new Enderman(*endermanPic_, this, player_);
					newWidth = endermanPic_->width();
					newHeight = endermanPic_->height();
					break;
			}
			
			// Initialize the enemy's position
			newEnemy->setPos
			(
				rand()%(width()  - newWidth  - 1),
				rand()%(height() - newHeight - 1)
			);
			
			// Add the enemy to the list of enemies and to the scene
			enemies_.push_back(newEnemy);
			scene_->addItem(newEnemy);
		}
		
		// Add a new item every specified number of periods
		if(timerCount_ % 376 == 0)
		{
			Thing* newItem = new Heart(*heartPic_, this, player_);
			// Initialize the item's position
			newItem->setPos
			(
				rand()%(width()  - heartPic_->width()  - 1),
				rand()%(height() - heartPic_->height() - 1)
			);
			items_.push_back(newItem);
			scene_->addItem(newItem);
		}
		
		// Update each Thing
		for(std::vector<Thing*>::iterator it = enemies_.begin(); it != enemies_.end(); ++it)
		{
			(*it)->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
			(*it)->move();
		}
		player_->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
		player_->move();
		
		// Every certain number of periods, speed up the enemies by decreasing the period
		if(periodCount_ % 200 == 0)
		{
			if(period_ > 2) period_--;
		}
		periodCount_++;
	}
	timerCount_++;
}
