#pragma once

#include <QMenu>
#include "Modules/MessageSystem/Messenger.h"

class FileMenu : public QMenu, Messenger
{
	Q_OBJECT
public:
	FileMenu(QWidget* parent = nullptr);

private slots:
	void loadFile();

private:
	void removeFilePrefix(std::string& filePath);
};


