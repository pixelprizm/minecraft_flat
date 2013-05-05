#ifndef GAMESPACE_H
#define GAMESPACE_H

// Standard
#include <vector>

// Qt
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>

// Local
#include "thing.h"
#include "steve.h"
#include "enemies.h"
#include "items.h"

class MainWindow;

/** Class for the game's gameplay.
*/
class GameSpace : public QGraphicsView
{
	Q_OBJECT
	
	public:
		explicit GameSpace(MainWindow* parent);
		~GameSpace();
		
		// Modifiers
		void startNewGame();
		void pauseGame(bool pause);
		void mouseMoveEvent(QMouseEvent* event);//QGraphicsSceneMouseEvent* event);
		
		// Accessors
		/** Get a pointer to the scene */
		QGraphicsScene* scene() { return scene_; }
		/** Get whether a game is currently in progress */
		bool gameInProgress() { return gameInProgress_; }
		/** Get a pointer to the parent */
		MainWindow* parent() { return parent_; }
		/* Get a reference to the current score */
		int& score() { return score_; }
		/* Get a reference to the game-over-flag */
		bool& gameOverFlag() { return gameOverFlag_; }
		/* Get a pointer to the player */
		Steve* player() { return player_; }
	
	public slots:
		void handleTimer();
	
	private:
		/* pointer to the parent MainWindow */
		MainWindow* parent_;
		/* the scene inside this view */
		QGraphicsScene* scene_;
		/* pointer to the graphics item for the background */
		QGraphicsPixmapItem* backgroundPicItem_;
			/* pointer to the picture used as the background */
			QPixmap* backgroundPic_;
		/* pointer to the player */
		Steve* player_;
			/* pointer to the picture for the player */
			QPixmap* stevePic_;
		/* vector full of the list of enemies */
		std::vector<Thing*> enemies_;
			/* pointer to the picture for zombies */
			QPixmap* zombiePic_;
			/* pointer to the picture for spiders */
			QPixmap* spiderPic_;
			/* pointer to the picture for creepers */
			QPixmap* creeperPic_;
			/* pointer to the picture for skeletons */
			QPixmap* skeletonPic_;
			/* pointer to the picture for endermen */
			QPixmap* endermanPic_;
		/* vector full of the list of items */
		std::vector<Item*> items_;
			/* pointer to the picture for hearts */
			QPixmap* heartPic_;
			/* pointer to the picture for strength potions */
			QPixmap* potionStrengthPic_;
		/* whether there is currently a game in progress (the only time this is false is when you first start the game */
		bool gameInProgress_;
		/* pointer to the timer data used for animation */
		QTimer* timer_;
		/* increments each timer pulse. */
		int timerCount_;
		/* number of timer pulses to wait before updating the enemies */
		int period_;
		/* increments each time a period passes */
		int periodCount_;
		/* increments once for every certain number of periods */
		int score_;
		/* indicates whether or not to increment the score */
		bool gameOverFlag_;
};

#endif // GAMESPACE_H
