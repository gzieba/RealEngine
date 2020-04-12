#include "FileMenu.h"
#include "source/Common/logging.h"

FileMenu::FileMenu(QWidget* parent) : QMenu(parent)
{
	setTitle("File");
	QAction* loadFile = addAction("Open File");

	connect(loadFile, &QAction::triggered, this, &FileMenu::loadFile);
}

void FileMenu::loadFile()
{
	LOG(INFO) << LOCATION << "loadFile pressed";
}
