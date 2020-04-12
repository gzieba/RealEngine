#include "FileMenu.h"
#include "source/Common/logging.h"
#include <QFileDialog>

FileMenu::FileMenu(QWidget* parent) : QMenu(parent)
{
	setTitle("File");
	QAction* loadFile = addAction("Open File");

	connect(loadFile, &QAction::triggered, this, &FileMenu::loadFile);
}

void FileMenu::loadFile()
{
	auto fileName = QFileDialog::getOpenFileUrl(this);
	LOG(INFO) << LOCATION << "loadFile pressed: " << fileName.toString().toStdString();
}
