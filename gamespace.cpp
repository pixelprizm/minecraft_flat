#include "gamespace.h"
#include "mainwindow.h"
#include <ctime> // for rand seed
#include <QMouseEvent>



/** Constructor. Loads pictures and builds the game area.
*/
GameSpace::GameSpace(MainWindow* parent)
:
	QGraphicsView(parent)
{
	parent_ = parent;
	gameInProgress_ = false;
	
	// Initialize scene
	scene_ = new QGraphicsScene;
	setScene(scene_);
	
	// Create the background (important that this is the first image added to the scene)
	backgroundPic_ = new QPixmap("images/sand_background_800.png");
	backgroundPicItem_ = new QGraphicsPixmapItem(*backgroundPic_);
	scene_->addItem(backgroundPicItem_);
	
	// Initialize player
	stevePic_ = new QPixmap("images/steve.png");
	player_ = NULL; // we will initialize Steve in the first game
	
	// Initialize pixmaps for enemies
	zombiePic_ = new QPixmap("images/zombie.png");
	spiderPic_ = new QPixmap("images/spider.png");
	creeperPic_ = new QPixmap("images/creeper.png");
	skeletonPic_ = new QPixmap("images/skeleton.png");
	endermanPic_ = new QPixmap("images/enderman.png");
	
	// Initialize heart item
	heartPic_ = new QPixmap("images/heart.png");
	
	// Initialize timer
	timer_ = new QTimer(this);
	timer_->setInterval(1); // this is kept low so that the player's update speed is fast
	connect(timer_, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	// Initialize values used in controlling speed of the game
	timerCount_ = 0;
	period_ = 30;
	periodCount_ = 1;
	
	// Set mouse flags
	setMouseTracking(true);
	setFocus();
	
	// Initialize score & game over flag
	score_ = 0;
	gameOverFlag_ = false;
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
		while(!hearts_.empty())
		{
			delete hearts_.back();
			hearts_.pop_back();
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
	
	if(player_) {delete player_;} // get rid of old player so we create a new one, correctly initialized
	
	// Initialize player values
	player_ = new Steve(*stevePic_, this);
	player_->setPos(400,300);
	scene_->addItem(player_);
	
	// Initialize label that displays number of lives
	parent()->healthLabelUI->setText("Health:");
	parent()->healthUI->setText(QString::number(player_->lives()));
	
	// If there was a previous game, get rid of the enemies (they remove themselves from the scene)
	if(gameInProgress_)
	{
		while(!enemies_.empty())
		{
			delete enemies_.back();
			enemies_.pop_back();
		}
		while(!hearts_.empty())
		{
			delete hearts_.back();
			hearts_.pop_back();
		}
	}
	
	
	
	// Initialize values used in controlling speed of the game
	timerCount_ = 0;
	period_ = 30;
	periodCount_ = 1; // it's 1 so that enemies don't spawn instantly
	
	// Initialize score
	parent()->scoreLabelUI->setText("Score:");
	score_ = 0;
	parent()->scoreUI->setText(QString::number(score_));
	gameOverFlag_ = false;
	
	// Start the game!
	gameOverFlag_ = false;
	timer_->start();
	gameInProgress_ = true;
}

/** Freeze or resume gameplay.
*	@param pause If true, pause the game; if false, resume the game
*/
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
		if(periodCount_ % 83 == 0)
		{
			Thing* newEnemy = NULL;
			QPixmap* newEnemyPic = NULL;
			switch(rand()%5)
			{
				case 0: newEnemy = new Zombie(*zombiePic_, this, player_);
					newEnemyPic = zombiePic_;
					break;
				case 1: newEnemy = new Spider(*spiderPic_, this, player_);
					newEnemyPic = spiderPic_;
					break;
				case 2: newEnemy = new Creeper(*creeperPic_, this, player_);
					newEnemyPic = creeperPic_;
					break;
				case 3: newEnemy = new Skeleton(*skeletonPic_, this, player_);
					newEnemyPic = skeletonPic_;
					break;
				case 4: newEnemy = new Enderman(*endermanPic_, this, player_);
					newEnemyPic = endermanPic_;
					break;
			}
			
			// Initialize the enemy's position
			newEnemy->setPos
			(
				rand()%(WINDOW_MAX_X - newEnemyPic->width() ) + (newEnemyPic->width()  / 2),
				rand()%(WINDOW_MAX_Y - newEnemyPic->height()) + (newEnemyPic->height() / 2)
			);//        ^rand range                              ^moves the enemy onto the view
			
			// Add the enemy to the list of enemies and to the scene
			enemies_.push_back(newEnemy);
			scene_->addItem(newEnemy);
		}
		
		// Add a new heart every specified number of periods
		if(periodCount_ % 376 == 0)
		{
			Thing* newItem = new Heart(*heartPic_, this, player_);
			// Initialize the item's position
			newItem->setPos
			(
				rand()%(WINDOW_MAX_X - heartPic_->width() ) + (heartPic_->width()  / 2),
				rand()%(WINDOW_MAX_Y - heartPic_->height()) + (heartPic_->height() / 2)
			);
			hearts_.push_back(newItem);
			scene_->addItem(newItem);
		}
		
		// Update each enemy & check for collisions
		for(unsigned int i = 0; i < enemies_.size(); i++)
		{
			enemies_[i]->updatePrecisePos(WINDOW_MAX_X, WINDOW_MAX_Y);
			enemies_[i]->move();
			
			if(enemies_[i]->collidesWithItem(player_))
			{
				delete enemies_[i];
				enemies_.erase(enemies_.begin()+i);
				player_->changeHealth(-1);
				if(gameOverFlag_) return;
			}
		}
		// Check for collisions between hearts and the player
		for(unsigned int i = 0; i < hearts_.size(); i++)
		{
			if(hearts_[i]->collidesWithItem(player_))
			{
				delete hearts_[i];
				hearts_.erase(hearts_.begin()+i);
				player_->changeHealth(+1);
				score_+=100;
			}
		}
		
		// Every certain number of periods, speed up the enemies by decreasing the period
		if(periodCount_ % 300 == 0)
		{
			if(period_ > 8) period_--;
			//DEBUG
			//	player_->changeHealth(-10);
		}
		periodCount_++;
		
		// Update score
		if(periodCount_ % 4 == 0 && !gameOverFlag_)
		{
			score_++;
			parent()->scoreUI->setNum(score_);
		}
	}
	timerCount_++;
}
