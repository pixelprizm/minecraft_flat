#ifndef GAMESPACE_H
#define GAMESPACE_H

// Standard
#include <vector>

// Qt
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

// Local
#include "thing.h"

class MainWindow;

class GameSpace : public QGraphicsView
{
	Q_OBJECT
	
	public:
		GameSpace(MainWindow* parent);
		// Accessors
		/** Get a pointer to the scene */
		QGraphicsScene* scene() { return scene_; }
	private:
		QGraphicsScene* scene_;
		std::vector<Thing*> enemies_;
		std::vector<Thing*> items_;
		QPixmap* zombie_;
		QPixmap* spider_;
		QPixmap* creeper_;
		QPixmap* skeleton_;
		QPixmap* enderman_;
		QPixmap* heart_;
		QPixmap* steve_;
};

#endif // GAMESPACE_H
