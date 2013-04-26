#include "gamespace.h"
#include "mainwindow.h"

/**
*/
GameSpace::GameSpace(MainWindow* parent)
{
	scene_ = new QGraphicsScene;
	setScene(scene_);
	zombie_ = new QPixmap("images/zombie.png");
	spider_ = new QPixmap("images/spider.png");
	creeper_ = new QPixmap("images/creeper.png");
	skeleton_ = new QPixmap("images/skeleton.png");
	enderman_ = new QPixmap("images/enderman.png");
	steve_ = new QPixmap("images/steve.png");
}

void GameSpace::startNewGame()
{
	
}
