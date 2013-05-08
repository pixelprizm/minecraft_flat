#include "mainwindow.h"
#include "gamespace.h"

#include <QMessageBox>
#include <QInputDialog>

#include <fstream>
#include <algorithm> // for sorting scores

using namespace std;


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
				usernameUI = new QLabel(this);
				usernameUI->setAlignment(Qt::AlignHCenter);
			leftLayoutUI->addWidget(usernameUI);
			// Health
				healthLayoutUI = new QHBoxLayout;
				// The word "health:"
					healthLabelUI = new QLabel(this); // this is not set to "Health:" until the first game starts
					healthLabelUI->setAlignment(Qt::AlignLeft);
					healthLabelUI->setFixedWidth(80);
				healthLayoutUI->addWidget(healthLabelUI);
				// Health value
					healthUI = new QLabel(this);
					healthUI->setAlignment(Qt::AlignRight);
					healthUI->setFixedWidth(80); // Makes it so that increasing numbers do not mess up the width
				healthLayoutUI->addWidget(healthUI);
			leftLayoutUI->addLayout(healthLayoutUI);
			// Score
				scoreLayoutUI = new QHBoxLayout;
				// The word "score:"
					scoreLabelUI = new QLabel(this); // this is not set to "Score:" until the first game starts
					scoreLabelUI->setAlignment(Qt::AlignLeft);
					scoreLabelUI->setFixedWidth(80);
				scoreLayoutUI->addWidget(scoreLabelUI);
				// Score value
					scoreUI = new QLabel(this);
					scoreUI->setAlignment(Qt::AlignRight);
					scoreUI->setFixedWidth(80); // Makes it so that increasing numbers do not mess up the width
				scoreLayoutUI->addWidget(scoreUI);
			leftLayoutUI->addLayout(scoreLayoutUI);
			// Invincibility
				invincibleLayoutUI = new QHBoxLayout;
				// The word "Invincible for:"
					invincibleLabelUI = new QLabel(this); // this is not set to "..." until the player becomes invincible
					invincibleLabelUI->setAlignment(Qt::AlignLeft);
					invincibleLabelUI->setFixedWidth(90);
				invincibleLayoutUI->addWidget(invincibleLabelUI);
				// Invincible value
					invincibleUI = new QLabel(this);
					invincibleUI->setAlignment(Qt::AlignRight);
					invincibleUI->setFixedWidth(70);
				invincibleLayoutUI->addWidget(invincibleUI);
			leftLayoutUI->addLayout(invincibleLayoutUI);
			// High scores list
				highScoresLayoutUI = new QVBoxLayout;
				// The words "High Scores:"
					highScoresLabelUI = new QLabel("Top 20 Scores:",this);
				highScoresLayoutUI->addWidget(highScoresLabelUI);
				// The high scores list box
					highScoresListUI = new QListWidget(this);
				highScoresLayoutUI->addWidget(highScoresListUI);
			leftLayoutUI->addLayout(highScoresLayoutUI);
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
	
	loadScores();
}



// ===============================================================================
// -------------------------------- HELPER FUNCTIONS -----------------------------
// ===============================================================================

/** Helper function to load scores from the file and fill up scoreData_. Called by the constructor.
*/
void MainWindow::loadScores()
{
	// Load scores
	ifstream scoreFile("scores.txt", ios::in);
	while(!scoreFile.eof())
	{
		ScorePair newScorePair;
		scoreFile >> newScorePair.first; // puts the score in
		if(newScorePair.first == 0) continue; // don't keep scores that are zero, in case any exist
		scoreFile >> ws; // extracts leading whitespace characters
		getline(scoreFile, newScorePair.second); // puts the username in
		if(!newScorePair.second.empty()) scoreData_.push_back(newScorePair);
	}
	sort(scoreData_.begin(), scoreData_.end());
	
	updateHighScoresList();
}

/** Helper function to save the current score and username, as well as all the current known high scores to the scores file
*/
void MainWindow::saveScores()
{
	if(gameSpaceUI->gameInProgress())
	{
		ScorePair currScorePair;
		currScorePair.first = gameSpaceUI->score();
		currScorePair.second = username_;
		if(!currScorePair.second.empty()) // if a username was entered
			scoreData_.push_back(currScorePair);
	}
	sort(scoreData_.begin(), scoreData_.end());
	scoreData_.erase(scoreData_.begin(), scoreData_.begin()+scoreData_.size()-20); // remove lowest scores if there are more than 20 scores. This is a slow operation because it's popping from the front of a vector, but that's okay because there should only ever be a maximum of 21 items.
	
	ofstream scoreFile("scores.txt", ios::out);
	for(unsigned int i = 0; i < scoreData_.size(); i++)
	{
		scoreFile << scoreData_[i].first << " " << scoreData_[i].second << endl;
	}
}

/** Helper function to update the UI scorelist with the scores and usernames in scoreData
*/
void MainWindow::updateHighScoresList()
{
	highScoresListUI->clear();
	for(int i = scoreData_.size()-1; i >= 0; i--)
	{
		QString temp;
		temp += QString::number(scoreData_[i].first);
		if(scoreData_[i].first < 10000) temp += "  ";
		if(scoreData_[i].first < 1000) temp += "  ";
		if(scoreData_[i].first < 100) temp += "  ";
		if(scoreData_[i].first < 10) temp += "  ";
		temp += "  ";
		temp += scoreData_[i].second.c_str();
		highScoresListUI->addItem(temp);
	}
}

/** Helper function to update the labels
*/
void MainWindow::updateLabels()
{
	if(gameSpaceUI->gameInProgress())
	{
		usernameUI->setText(username_.c_str());
		healthLabelUI->setText("Health:");
		healthUI->setText(QString::number(gameSpaceUI->player()->health()));
		scoreLabelUI->setText("Score:");
		scoreUI->setText(QString::number(gameSpaceUI->score()));
		if(gameSpaceUI->player()->invincible())
		{
			invincibleLabelUI->setText("Invincible for:");
			invincibleUI->setText(QString::number(gameSpaceUI->player()->invincible()));
		}
		else
		{
			invincibleLabelUI->setText("");
			invincibleUI->setText("");
		}
	}
	else
	{
		usernameUI->setText("");
		healthLabelUI->setText("");
		healthUI->setText("");
		scoreLabelUI->setText("");
		scoreUI->setText("");
		invincibleLabelUI->setText("");
		invincibleUI->setText("");
	}
}

/** Called when the player dies. Prompts the user to start a new game or quit.
*/
void MainWindow::gameOver()
{
	gameSpaceUI->pauseGame(true);
	gameSpaceUI->gameOverFlag() = true;
	
	saveScores();
	
	updateHighScoresList();
	
	// Pop up game over box
	QMessageBox gameOverPrompt(gameSpaceUI); // passing gameSpaceUI centers the dialog box over the gameSpace
	gameOverPrompt.setWindowTitle("Game Over!");
	QString deathText("Score: ");
	deathText += QString::number(gameSpaceUI->score());
	deathText += "\nScore saved.";
	gameOverPrompt.setText(deathText);
	gameOverPrompt.setInformativeText("Do want to start new game?");
	gameOverPrompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	gameOverPrompt.setDefaultButton(QMessageBox::Yes);
	int choice = gameOverPrompt.exec();
	if(choice==QMessageBox::No) {qApp->quit(); return;}
	
	enterUsername();
	
	gameSpaceUI->startLevel(false, 1);
}

/** Prompts the user to enter a username. On repeated games, starts out with the last entered username by default.
*/
void MainWindow::enterUsername()
{
	username_ = QInputDialog::getText(this, tr("Enter Username"), tr("You must enter a username for your score to be saved."), QLineEdit::Normal, username_.c_str()).toStdString();
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
		int choice = newGamePrompt.exec();
		if(choice==QMessageBox::No) {gameSpaceUI->pauseGame(false); return;}
	}
	
	saveScores();
	
	enterUsername();
	
	updateHighScoresList();
	
	gameSpaceUI->startLevel(false, 1);
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
		int choice = quitPrompt.exec();
		if(choice==QMessageBox::No) {gameSpaceUI->pauseGame(false); return;}
	}
	saveScores();
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
		pausePrompt.setMinimumWidth(600); // otherwise it's way too narrow
		pausePrompt.setText("Game paused.");
		pausePrompt.setInformativeText("Press OK to resume.");
		pausePrompt.setStandardButtons(QMessageBox::Ok);
		pausePrompt.buttons().at(0)->setFixedWidth(2*pausePrompt.buttons().at(0)->width());
		pausePrompt.exec();
		gameSpaceUI->pauseGame(false);
	}
}
