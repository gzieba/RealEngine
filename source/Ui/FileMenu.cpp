#include "FileMenu.h"
#include "Common/logging.h"
#include <QFileDialog>

FileMenu::FileMenu(QWidget* parent) : QMenu(parent)
{
	setTitle("File");
	QAction* loadFile = addAction("Open File");

	connect(loadFile, &QAction::triggered, this, &FileMenu::loadFile);
}

void FileMenu::loadFile()
{
	auto fileName = QFileDialog::getOpenFileUrl(this).toString().toStdString();
	LOG(INFO) << LOCATION << "loadFile pressed: " << fileName;
	removeFilePrefix(fileName);
	sendMessage({Message::Msg::LoadModel, fileName});
}

void FileMenu::removeFilePrefix(std::string &filePath)
{
	std::string filePrefix = "file://";
	auto position = filePath.find(filePrefix);

	if (position != std::string::npos)
	{
		// If found then erase it from string
		filePath.erase(position, filePrefix.length());
	}
}
