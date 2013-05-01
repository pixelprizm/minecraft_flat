#include "mainwindow.h"
#include "gamespace.h"

#include <QInputDialog>

/** Constructor. Builds the game's main window UI.
*/
MainWindow::MainWindow()
{
	this->setWindowTitle("Minecraft Flat!");
	
	// Layout and GUI items
	mainLayoutUI = new QHBoxLayout;
		// Left User Interface e.g. Buttons
			leftLayoutUI = new QVBoxLayout;
			leftLayoutUI->setAlignment(Qt::AlignTop);
			// Start button
				startButtonUI = new QPushButton("New Game", this);
				connect(startButtonUI, SIGNAL(clicked()), this, SLOT(startNewGame()));
			leftLayoutUI->addWidget(startButtonUI);
			// Quit button
				quitButtonUI = new QPushButton("Quit", this);
				connect(quitButtonUI, SIGNAL(clicked()), this, SLOT(quitGame()));
			leftLayoutUI->addWidget(quitButtonUI);
			// Pause button
				pauseButtonUI = new QPushButton("Pause", this);
				connect(pauseButtonUI, SIGNAL(clicked()), this, SLOT(pauseGame()));
			leftLayoutUI->addWidget(pauseButtonUI);
			// Username
				usernameUI = new QLabel("", this);
				usernameUI->setAlignment(Qt::AlignHCenter);
			leftLayoutUI->addWidget(usernameUI);
			// Health
				healthLayoutUI = new QHBoxLayout;
				// The word "health:"
					healthLabelUI = new QLabel("", this); // this is not set to "Health:" until the first game starts
					healthLabelUI->setAlignment(Qt::AlignLeft);
					healthLabelUI->setFixedWidth(80);
				healthLayoutUI->addWidget(healthLabelUI);
				// Health value
					healthUI = new QLabel("", this);
					healthUI->setAlignment(Qt::AlignRight);
					healthUI->setFixedWidth(80); // Makes it so that increasing numbers do not mess up the width
				healthLayoutUI->addWidget(healthUI);
			leftLayoutUI->addLayout(healthLayoutUI);
			// Score
				scoreLayoutUI = new QHBoxLayout;
				// The word "score:"
					scoreLabelUI = new QLabel("", this); // this is not set to "Score:" until the first game starts
					scoreLabelUI->setAlignment(Qt::AlignLeft);
				scoreLayoutUI->addWidget(scoreLabelUI);
				// Score value
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

/** Called when the player dies. Prompts the user to start a new game or quit.
*/
void MainWindow::gameOver()
{
	gameSpaceUI->pauseGame(true);
	gameSpaceUI->gameOverFlag() = true;
	QMessageBox gameOverPrompt(gameSpaceUI); // centers the dialog box over the gameSpace
	gameOverPrompt.setWindowTitle("Game Over!");
	QString* deathText = new QString("Score: ");
	*deathText += QString::number(gameSpaceUI->score());
	//eventually, save the score to a file here.
	gameOverPrompt.setText(*deathText);
	gameOverPrompt.setInformativeText("Do want to start new game?");
	gameOverPrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	gameOverPrompt.setDefaultButton(QMessageBox::Yes);
	int choice = gameOverPrompt.exec();
	if(choice==QMessageBox::No) {qApp->quit(); return;}
	
	enterUsername();
}

/** Prompts the user to enter a username. On repeated games, starts out with the last entered username by default.
*/
void MainWindow::enterUsername()
{
	//bool ok = false;
	QString username = QInputDialog::getText(this, tr("Username"), tr("Enter username:"), QLineEdit::Normal, usernameUI->text());
	
	usernameUI->setText(username);
	
	gameSpaceUI->startNewGame();
}



// ===========================================================================
// ------------------------------- SLOTS -------------------------------------
// ===========================================================================

/** Start a new game. Prompts the user first if a game is in progress.
*/
void MainWindow::startNewGame()
{
	// Check & prompt the user if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox newGamePrompt(gameSpaceUI);
		newGamePrompt.setWindowTitle("Start New Game");
		newGamePrompt.setText("Game is in progress.");
		newGamePrompt.setInformativeText("Do you really want to start new game?");
		newGamePrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		// newGamePrompt.setDefaultButton(QMessageBox::No); // looks bad
		int choice = newGamePrompt.exec();
		if(choice==QMessageBox::No) {gameSpaceUI->pauseGame(false); return;}
	}
	
	enterUsername();
}

/** Prompt the user to quit the game.
*/
void MainWindow::quitGame()
{
	// Check if a game is in progress
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox quitPrompt(gameSpaceUI);
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

/** Pauses and presents a pop-up until the user resumes
*/
void MainWindow::pauseGame()
{
	if(gameSpaceUI->gameInProgress())
	{
		gameSpaceUI->pauseGame(true);
		QMessageBox pausePrompt(gameSpaceUI);
		pausePrompt.setWindowTitle("Pause Game");
		pausePrompt.setMinimumWidth(600);
		pausePrompt.setText("Game paused.");
		pausePrompt.setInformativeText("Press OK to resume.");
		pausePrompt.setStandardButtons(QMessageBox::Ok);
		pausePrompt.buttons().at(0)->setFixedWidth(2*pausePrompt.buttons().at(0)->width());
		pausePrompt.exec();
		gameSpaceUI->pauseGame(false);
	}
}
