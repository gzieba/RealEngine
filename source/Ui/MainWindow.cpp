#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Common/logging.h"
#include "FileMenu.h"
#include "Ui/ObjectListWidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	setupMenu();

	m_ui->fileList = new ObjectListWidget(this);
	m_ui->fileList->setGeometry(QRect(500, 30, 271, 331));

	connect(m_ui->pushButton, &QPushButton::clicked, this, [this](){ sendMessage(MessageType::Test); });

}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::handleMessage(const Message &message)
{
	if(message.getMessageType() == MessageType::Test)
		LOG(TRACE) << "Button was pressed";
}

void MainWindow::closeEvent(QCloseEvent *)
{
	sendMessage(MessageType::Shutdown);
}

void MainWindow::setupMenu()
{
	m_ui->menubar->addMenu(new FileMenu(this));
}

