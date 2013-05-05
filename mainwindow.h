#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
	// needed in order to call qApp->close()
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QString>

#include "gamespace.h"
#include "steve.h" // for 

#define WINDOW_MAX_X 800
#define WINDOW_MAX_Y WINDOW_MAX_X*3/4

class MainWindow : public QWidget
{
	Q_OBJECT
	
	public: // Member functions
		explicit MainWindow();
		void gameOver();
		void enterUsernameAndStartGame();
		
		// Helper functions
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
			/** Pointer to layout for game area (used to center the game area within its layout area) */
			QVBoxLayout* gameSpaceLayoutUI;
				/** Pointer to gameplay area of the window */
				GameSpace* gameSpaceUI;
	
	private: // Data members
		QString username_;
};

#endif // MAINWINDOW_H
