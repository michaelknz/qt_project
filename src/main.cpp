#include "main_window.h"
#include <QApplication>

int main(int argc, char** argv) {
	QCoreApplication::addLibraryPath("C:/Qt/5.15.1/msvc2019_64/plugins");
	QApplication app(argc, argv);
	Main_Window wnd;
	wnd.show();
	app.exec();
	return 0;
}