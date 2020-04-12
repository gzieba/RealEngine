#pragma once

#include <QMenu>

class FileMenu : public QMenu
{
	Q_OBJECT
public:
	FileMenu(QWidget* parent = nullptr);

private slots:
	void loadFile();
};


