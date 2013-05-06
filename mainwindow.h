#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>	// needed in order to call qApp.quit()
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

#include <utility> // for pair (for ScorePair struct)
#include <vector> // for list of ScorePairs
#include <string>

#include "gamespace.h"

#define WINDOW_MAX_X 800
#define WINDOW_MAX_Y WINDOW_MAX_X*3/4


/** Struct for keeping track of scores--holds a score and a username and defines an operator for sorting
*/
struct ScorePair : public std::pair<int, std::string> // the std::pair is required because std::pair has swap() defined for it
{
	bool operator<(const ScorePair rhs) { return this->first < rhs.first; }
};



/** class for the window that contains the game
*/
class MainWindow : public QWidget
{
	Q_OBJECT
	
	public: // Member functions
		explicit MainWindow();
		void gameOver();
		void enterUsernameAndStartGame();
		
		// Helper functions
		void loadScores();
		void saveScores();
		void updateHighScoresList();
		void updateLabels();

	public slots:
		void startNewGame();
		void quitGame();
		void pauseGame();
	
	public: // UI elements
		/** Pointer to entire window's layout */
		QHBoxLayout* mainLayoutUI;
			/** Pointer to vertical layout to the left of the gameplay area */
			QVBoxLayout* leftLayoutUI;
				/** Pointer to start button */
				QPushButton* startButtonUI;
				/** Pointer to quit button */
				QPushButton* quitButtonUI;
				/** Pointer to pause button */
				QPushButton* pauseButtonUI;
				/** Pointer to username label */
				QLabel* usernameUI;
				/** Pointer to layout for health label and health value */
				QHBoxLayout* healthLayoutUI;
					/** Pointer to health label */
					QLabel* healthLabelUI;
					/** Pointer to health value */
					QLabel* healthUI;
				/** Pointer to layout for score label and score value */
				QHBoxLayout* scoreLayoutUI;
					/** Pointer to score label */
					QLabel* scoreLabelUI;
					/** Pointer to score value */
					QLabel* scoreUI;
				/** Pointer to layout for invincible label and player's invincible value */
				QHBoxLayout* invincibleLayoutUI;
					/** Pointer to score label */
					QLabel* invincibleLabelUI;
					/** Pointer to score value */
					QLabel* invincibleUI;
				/** Pointer to layout for high scores (contains just a label for high scores and the box of high scores */
				QVBoxLayout* highScoresLayoutUI;
					/** Pointer to high scores label */
					QLabel* highScoresLabelUI;
					/** Pointer to high scores box */
					QListWidget* highScoresListUI;
			/** Pointer to layout for game area (used to center the game area within its layout area) */
			QVBoxLayout* gameSpaceLayoutUI;
				/** Pointer to gameplay area of the window */
				GameSpace* gameSpaceUI;
	
	private: // Data members
		// note: use gameSpaceUI->score() for current score.
		/** Current user's username */
		std::string username_;
		/** list of score-username pairs */
		std::vector<ScorePair> scoreData_;
};

#endif // MAINWINDOW_H
