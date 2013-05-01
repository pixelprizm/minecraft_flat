#include "mainwindow.h"
#include "gamespace.h"

#include <iostream>

/** Constructor. Builds the game.
*/
MainWindow::MainWindow()
{
	this->setWindowTitle("Minecraft Flat Survival!");
	
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
			// Username
				userNameUI = new QLabel("", this);
				userNameUI->setAlignment(Qt::AlignRight);
			leftLayoutUI->addWidget(userNameUI);
			// Health
				healthLayoutUI = new QHBoxLayout;
					healthLabelUI = new QLabel("", this);
					healthLabelUI->setAlignment(Qt::AlignLeft);
					healthLabelUI->setFixedWidth(80);
				healthLayoutUI->addWidget(healthLabelUI);
					healthUI = new QLabel("", this);
					healthUI->setAlignment(Qt::AlignRight);
					healthUI->setFixedWidth(80); // Makes it so that increasing numbers do not mess up the width
				healthLayoutUI->addWidget(healthUI);
			leftLayoutUI->addLayout(healthLayoutUI);
			// Score
				scoreLayoutUI = new QHBoxLayout;
					scoreLabelUI = new QLabel("", this);
					scoreLabelUI->setAlignment(Qt::AlignLeft);
				scoreLayoutUI->addWidget(scoreLabelUI);
					scoreUI = new QLabel("", this);
					scoreUI->setAlignment(Qt::AlignRight);
				scoreLayoutUI->addWidget(scoreUI);
			leftLayoutUI->addLayout(scoreLayoutUI);
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

/** Called when the player dies
*/
void MainWindow::gameOver()
{
	gameSpaceUI->pauseGame(true);
	std::cout << "Game Over!" << std::endl;
	gameSpaceUI->gameOverFlag() = true;
	QMessageBox gameOverPrompt;
	gameOverPrompt.setWindowTitle("Game Over!");
	QString* deathText = new QString("Score: ");
	*deathText += QString::number(gameSpaceUI->score());
	//eventually, save the score here.
	gameOverPrompt.setText(*deathText);
	gameOverPrompt.setInformativeText("Do want to start new game?");
	gameOverPrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	int choice = gameOverPrompt.exec();
	if(choice==QMessageBox::No) {qApp->quit();}
	
	gameSpaceUI->startNewGame();
}



// ===========================================================================
// ------------------------------- SLOTS -------------------------------------
// ===========================================================================

/** Start a new game
*/
void MainWindow::startNewGame()
{
	// Check & prompt the user if a game is in progress
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
	//Add prompt for username
	
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
