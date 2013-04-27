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
	
	public slots:
		void handleTimer();
	
	private:
		MainWindow* parent_;
		QGraphicsScene* scene_;
		QGraphicsPixmapItem* backgroundPicItem_;
			QPixmap* backgroundPic_;
		Steve* player_;
			QPixmap* stevePic_;
		std::vector<Thing*> enemies_;
			QPixmap* zombiePic_;
			QPixmap* spiderPic_;
			QPixmap* creeperPic_;
			QPixmap* skeletonPic_;
			QPixmap* endermanPic_;
		std::vector<Thing*> items_;
			QPixmap* heartPic_;
		bool gameInProgress_;
		QTimer* timer_;
		int timerCount_;
		int period_;
		int periodCount_;
};

#endif // GAMESPACE_H
