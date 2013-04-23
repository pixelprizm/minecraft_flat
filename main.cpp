#include <QtGui/QApplication>
#include "mainwindow.h"

/** Main function, just starts the GUI program
* @param argc The number of arguments passed when running the program in the console
* @param argv An array of pointers to character arrays of the arguments
*/
int main(int argc, char* argv[])
{
	QApplication puz(argc, argv);
	MainWindow w;
	
	w.show();
	
	return puz.exec();
}
