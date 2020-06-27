#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Common/logging.h"
#include "FileMenu.h"
#include "Ui/ObjectListWidget.h"

#include <QOpenGLContext>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	m_ui->fileList->setObjectTransformWidget(m_ui->widget);
	QSurfaceFormat format;
	format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
	format.setMajorVersion(4);
	format.setMinorVersion(5);
	format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
	m_ui->openGLWidget->setFormat(format);
	m_ui->openGLWidget->makeCurrent();
	setupMenu();

	connect(m_ui->pushButton, &QPushButton::clicked, this, [this](){ sendMessage(MessageType::Test); });

}

MainWindow::~MainWindow()
{
	delete m_ui;
}

void MainWindow::handleMessage(const Message &message)
{
	if(message.getMessageType() == MessageType::Test)
	{
//		m_ui->openGLWidget->makeCurrent();
		LOG(TRACE) << "Button was pressed";
	}
}

void MainWindow::closeEvent(QCloseEvent *)
{
	sendMessage(MessageType::Shutdown);
}

void MainWindow::setupMenu()
{
	m_ui->menubar->addMenu(new FileMenu(this));
}

