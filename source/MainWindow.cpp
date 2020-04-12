#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Common/logging.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	connect(m_ui->pushButton, &QPushButton::clicked, this, [this](){ sendMessage(Message::Msg::Test); });

}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::handleMessage(const Message &message)
{
	if(message.getMessage() == Message::Msg::Test)
		LOG(INFO) << LOCATION << "Button was pressed";
}

