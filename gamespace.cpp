#include "gamespace.h"
#include "mainwindow.h"

/**
*/
GameSpace::GameSpace(MainWindow* parent)
{
	scene_ = new QGraphicsScene;
	setScene(scene_);
}
