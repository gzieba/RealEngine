#include "Ui/MainWindow.h"
#include "Common/logging.h"

#include "RealEngine.h"

INITIALIZE_EASYLOGGINGPP


#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RealEngine r;
	MainWindow w;
	w.show();
	return a.exec();
}
