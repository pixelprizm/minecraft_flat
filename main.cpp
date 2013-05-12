// Copyright (C) 2013 Eric Gauderman



#include <QtGui/QApplication>
#include <iostream> // for error message
#include "mainwindow.h"

/** Main function, just starts the GUI program
* @param argc The number of arguments passed when running the program in the console
* @param argv An array of pointers to character arrays of the arguments
*/
int main(int argc, char* argv[])
{
	if(argc < 2) { std::cerr << "Usage: " << argv[0] << " <scores-file-name>" << std::endl; return 1; }
	QApplication game(argc, argv);
	MainWindow w(argv[1]);
	
	w.show();
	
	return game.exec();
}
