#include "mainwindow.h"
#include "gamespace.h"

#include <iostream>
using namespace std;

/** Constructor. Builds the game.
*/
MainWindow::MainWindow()
{
	// Declarations:
		
	// Layout and GUI items
	mainLayoutUI = new QVBoxLayout(this);
		startQuitLayoutUI = new QHBoxLayout(this); //this line outputs at runtime: QLayout: Attempting to add QLayout "" to MainWindow "", which already has a layout
			startButtonUI = new QPushButton("Start New Game", this);
				connect(startButtonUI, SIGNAL(clicked()), this, SLOT(startNewGame()));
			startQuitLayoutUI->addWidget(startButtonUI);
			quitButtonUI = new QPushButton("Quit", this);
				connect(quitButtonUI, SIGNAL(clicked()), this, SLOT(quitGame()));
			startQuitLayoutUI->addWidget(quitButtonUI);
		mainLayoutUI->addLayout(startQuitLayoutUI);
		statusLabelUI = new QLabel("", this);
			statusLabelUI->setAlignment(Qt::AlignHCenter);
		mainLayoutUI->addWidget(statusLabelUI);
		gameSpaceLayoutUI = new QHBoxLayout(this); //this line outputs at runtime: QLayout: Attempting to add QLayout "" to MainWindow "", which already has a layout
cout << "yyyyyyyyyyyy1" << endl;
			gameSpaceUI = new GameSpace(this);
cout << "yyyyyyyyyyyy2" << endl;
				gameSpaceLayoutUI->setAlignment(Qt::AlignHCenter);
cout << "yyyyyyyyyyyy3" << endl;
				gameSpaceUI->setFixedWidth(WINDOW_MAX_X);
cout << "yyyyyyyyyyyy4" << endl;
				gameSpaceUI->setFixedHeight(gameSpaceUI->width());
cout << "yyyyyyyyyyyy5" << endl;
			gameSpaceLayoutUI->addWidget(gameSpaceUI);
cout << "yyyyyyyyyyyy0" << endl;
		mainLayoutUI->addLayout(gameSpaceLayoutUI);
		lowerLayoutUI = new QHBoxLayout(this);
			//health
			userNameUI = new QLabel("", this);
				userNameUI->setAlignment(Qt::AlignRight);
			lowerLayoutUI->addWidget(userNameUI);
			scoreUI = new QLabel("", this);
				scoreUI->setAlignment(Qt::AlignLeft);
			lowerLayoutUI->addWidget(scoreUI);
		mainLayoutUI->addLayout(lowerLayoutUI);
	//this->setLayout(mainLayoutUI);
}



// ===========================================================================
// ------------------------------- SLOTS -------------------------------------

/** Start a new game
*/
void MainWindow::startNewGame()
{
	cout << "Hi" << endl;
}

/** Prompt the user to quit
*/
void MainWindow::quitGame()
{
	// Check if a game is in progress
	// If not, just quit
	//qapp->quit()
	// If a game is in progress, 
	cout << "quit" << endl;
}
