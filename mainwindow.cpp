#include "mainwindow.h"
#include "gamespace.h"

#include <iostream>
using namespace std;

/** Constructor. Builds the game.
*/
MainWindow::MainWindow()
{
	// Layout and GUI items
	mainLayoutUI = new QHBoxLayout;
		// User Interface e.g. Buttons
		leftLayoutUI = new QVBoxLayout;
			leftLayoutUI->setAlignment(Qt::AlignTop);
			startButtonUI = new QPushButton("New Game", this);
				connect(startButtonUI, SIGNAL(clicked()), this, SLOT(startNewGame()));
			leftLayoutUI->addWidget(startButtonUI);
			quitButtonUI = new QPushButton("Quit", this);
				connect(quitButtonUI, SIGNAL(clicked()), this, SLOT(quitGame()));
			leftLayoutUI->addWidget(quitButtonUI);
			pauseButtonUI = new QPushButton("Pause", this);
				connect(pauseButtonUI, SIGNAL(clicked()), this, SLOT(pauseGame()));
			leftLayoutUI->addWidget(pauseButtonUI);
			//healthUI = new QLabel(
			userNameUI = new QLabel("", this);
				userNameUI->setAlignment(Qt::AlignRight);
			leftLayoutUI->addWidget(userNameUI);
			scoreUI = new QLabel("", this);
				scoreUI->setAlignment(Qt::AlignLeft);
			leftLayoutUI->addWidget(scoreUI);
			statusLabelUI = new QLabel("", this);
				statusLabelUI->setAlignment(Qt::AlignHCenter);
			leftLayoutUI->addWidget(statusLabelUI);
		mainLayoutUI->addLayout(leftLayoutUI);
		
		// Gameplay Area
		gameSpaceLayoutUI = new QVBoxLayout;
			gameSpaceLayoutUI->setAlignment(Qt::AlignHCenter);
			gameSpaceUI = new GameSpace(this);
				gameSpaceUI->setFixedWidth(WINDOW_MAX_X+2);
				gameSpaceUI->setFixedHeight(WINDOW_MAX_Y+2);
			gameSpaceLayoutUI->addWidget(gameSpaceUI);
		mainLayoutUI->addLayout(gameSpaceLayoutUI);
		
	this->setLayout(mainLayoutUI);
}



// ===========================================================================
// ------------------------------- SLOTS -------------------------------------
// ===========================================================================

/** Start a new game
*/
void MainWindow::startNewGame()
{
	// Check if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox newGamePrompt;
		newGamePrompt.setWindowTitle("Start New Game");
		newGamePrompt.setText("Game is in progress.");
		newGamePrompt.setInformativeText("Do you really want to start new game?");
		newGamePrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		// newGamePrompt.setDefaultButton(QMessageBox::No); // looks bad
		int choice = newGamePrompt.exec();
		if(choice==QMessageBox::No) {gameSpaceUI->pauseGame(false); return;}
	}
	gameSpaceUI->startNewGame();
}

/** Prompt the user to quit
*/
void MainWindow::quitGame()
{
	// Check if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox quitPrompt;
		quitPrompt.setWindowTitle("Quit Game");
		quitPrompt.setText("Game is in progress.");
		quitPrompt.setInformativeText("Do you really want to quit?");
		quitPrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		// quitPrompt.setDefaultButton(QMessageBox::No); // looks bad
		int choice = quitPrompt.exec();
		if(choice==QMessageBox::No) {gameSpaceUI->pauseGame(false); return;}
	}
	qApp->quit();
}

/** Pauses and presents a pop-up to the user to resume
*/
void MainWindow::pauseGame()
{
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox pausePrompt;
		pausePrompt.setWindowTitle("Pause Game");
		pausePrompt.setMinimumWidth(600);
		pausePrompt.setText("Game paused.");
		pausePrompt.setInformativeText("Press OK to resume.");
		pausePrompt.setStandardButtons(QMessageBox::Ok);
		pausePrompt.exec();
		gameSpaceUI->pauseGame(false);
	}
}
