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
	mainLayoutUI = new QHBoxLayout;
		leftLayoutUI = new QVBoxLayout;
			leftLayoutUI->setAlignment(Qt::AlignTop);
			startButtonUI = new QPushButton("Start New Game", this);
				connect(startButtonUI, SIGNAL(clicked()), this, SLOT(startNewGame()));
			leftLayoutUI->addWidget(startButtonUI);
			quitButtonUI = new QPushButton("Quit", this);
				connect(quitButtonUI, SIGNAL(clicked()), this, SLOT(quitGame()));
			leftLayoutUI->addWidget(quitButtonUI);
		mainLayoutUI->addLayout(leftLayoutUI);
		statusLabelUI = new QLabel("", this);
			statusLabelUI->setAlignment(Qt::AlignHCenter);
		mainLayoutUI->addWidget(statusLabelUI);
		gameSpaceLayoutUI = new QHBoxLayout;
			gameSpaceLayoutUI->setAlignment(Qt::AlignHCenter);
			gameSpaceUI = new GameSpace(this);
				gameSpaceUI->setFixedWidth(WINDOW_MAX_X);
				gameSpaceUI->setFixedHeight(gameSpaceUI->width());
			gameSpaceLayoutUI->addWidget(gameSpaceUI);
		mainLayoutUI->addLayout(gameSpaceLayoutUI);
		rightLayoutUI = new QVBoxLayout;
			//health
			userNameUI = new QLabel("", this);
				userNameUI->setAlignment(Qt::AlignRight);
			rightLayoutUI->addWidget(userNameUI);
			scoreUI = new QLabel("", this);
				scoreUI->setAlignment(Qt::AlignLeft);
			rightLayoutUI->addWidget(scoreUI);
		mainLayoutUI->addLayout(rightLayoutUI);
	this->setLayout(mainLayoutUI);
}



// ===========================================================================
// ------------------------------- SLOTS -------------------------------------

/** Start a new game
*/
void MainWindow::startNewGame()
{
	// Check if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		QMessageBox newGamePrompt;
		newGamePrompt.setWindowTitle("Start New Game");
		newGamePrompt.setText("Game is in progress.");
		newGamePrompt.setInformativeText("Do you really want to start new game?");
		newGamePrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		newGamePrompt.setDefaultButton(QMessageBox::No);
		int choice = newGamePrompt.exec();
		if(choice==QMessageBox::No) return;
	}
}

/** Prompt the user to quit
*/
void MainWindow::quitGame()
{
	// Check if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		QMessageBox quitPrompt;
		quitPrompt.setWindowTitle("Quit Game");
		quitPrompt.setText("Game is in progress.");
		quitPrompt.setInformativeText("Do you really want to quit?");
		quitPrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		quitPrompt.setDefaultButton(QMessageBox::No);
		int choice = quitPrompt.exec();
		if(choice==QMessageBox::No) return;
	}
	qApp->quit();
}
