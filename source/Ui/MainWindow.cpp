#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "source/Common/logging.h"
#include "FileMenu.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	setupMenu();

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

void MainWindow::setupMenu()
{
	m_ui->menubar->addMenu(new FileMenu(this));
}

