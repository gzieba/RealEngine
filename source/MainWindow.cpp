#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Common/logging.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, &QPushButton::clicked, this, [this](){ sendMessage(Message::Msg::Test); });

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::handleMessage(const Message &message)
{
	if(message.getMessage() == Message::Msg::Test)
		LOG(INFO) << LOCATION << "Button was pressed";
}

