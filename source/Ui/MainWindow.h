#pragma once

#include <QMainWindow>
#include "source/MessageSystem/Messenger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, Messenger
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void handleMessage(const Message &) override;

private:
	void setupMenu();

	Ui::MainWindow *m_ui;
};

