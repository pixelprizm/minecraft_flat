#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
	// needed in order to call qApp->close()
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "gamespace.h"

#define WINDOW_MAX_X 600

class MainWindow : public QWidget
{
	Q_OBJECT
	
	public: // Member functions
		explicit MainWindow();

	public slots:
		void startNewGame();
		void quitGame();
	
	private: // UI elements
		QVBoxLayout* mainLayoutUI;
			QHBoxLayout* startQuitLayoutUI;
				QPushButton* startButtonUI;
				QPushButton* quitButtonUI;
			QLabel* statusLabelUI;
			QHBoxLayout* gameSpaceLayoutUI;
				GameSpace* gameSpaceUI;
			QHBoxLayout* lowerLayoutUI;
				QLabel* userNameUI;
				QLabel* scoreUI;
};

#endif // MAINWINDOW_H
