#include "MainWindow.h"
#include "Common/logging.h"

INITIALIZE_EASYLOGGINGPP


#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
