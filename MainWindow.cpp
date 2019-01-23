#include "App.h"
#include "UserData.h"
#include "DataBase.h"

#include "MainWindow.h"
#include "Widget.h"

#include <QAction>
#include <QDebug>
#include <QLabel>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QMenuBar>
#include <QFile>
#include <QApplication>
#include <QDateTime>
#include <QDir>

#include "LogWidget.h"
#include "UserManager.h"
#include "Login.h"

MainWindow *MainWindow::s_instance = 0;
void MainWindow::initStackedWidget()
{
    this->setCentralWidget(m_stackedWidget);
}

void MainWindow::initUserManagerWidget()
{
    QAction *userManagerAction = new QAction(tr("用户管理"), this);
    QAction *openLogAction = new QAction(tr("打开日志"), this);
    //this->addAction(userManagerAction);
    //this->menuBar()->addAction(userManagerAction);
    QMenu *userMenu = new QMenu(tr("帮助"),this);
    userMenu->addAction(userManagerAction);
    userMenu->addAction(openLogAction);
    this->menuBar()->addMenu(userMenu);

    connect(userManagerAction, &QAction::triggered,
            this, &MainWindow::userManaggerActionClicked);

    connect(openLogAction, &QAction::triggered,
            this, &MainWindow::openLogActionClicked);
}

void MainWindow::initDataBaseManager(QString dbPath)
{
    Q_ASSERT(QFile(dbPath).exists());
    m_databaseManager->setDatabaseName(dbPath);
    m_databaseManager->setConnectionName(QApplication::applicationName());
    //m_databaseManager->setTableCount(1);
    Q_ASSERT(m_databaseManager->init() == true);
}

void MainWindow::userManaggerActionClicked()
{
    UserManager *manager = new UserManager(this);
    if (this->centralWidget() == m_stackedWidget)
    {
        if (m_databaseManager->contains("user"))
        {
            manager->setModel(m_databaseManager->model("user"));
        }
        this->setCurrentWidget(manager, true);
    }
}

void MainWindow::openLogActionClicked()
{
    LogWidget *logWidget = new LogWidget(this);
    logWidget->fromFile(theApp->logFilePath());
    logWidget->initLogSelector(QFileInfo(theApp->logFilePath()).absolutePath());
    //"F:/SVNCode30.15/build-CarCarStudio-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/2019.01.16 16_24_59.laquaLog.txt"
    this->setCurrentWidget(logWidget, true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_databaseManager(new DataBaseManager(this))
    , m_stackedWidget(new QStackedWidget(this))
    , m_currentUserName("debug")
{
    //initStackedWidget(); //必须在子类中调用一遍，否则不能使用setCurrentWidget()
}

MainWindow::~MainWindow()
{
    foreach (QWidget *widget, m_stackedWidgetIsDelete.keys()) {
        m_stackedWidgetIsDelete.remove(widget);
        delete widget;
    }

}

MainWindow *MainWindow::instance()
{
    if(s_instance == NULL)
    {
        //qDebug() << "MainWindow instance";
        s_instance = new MainWindow;
    }
    return s_instance;
}
DataBaseManager *MainWindow::database() const
{
    return m_databaseManager;
}

void MainWindow::setDatabase(DataBaseManager *database)
{
    m_databaseManager = database;
}

bool MainWindow::login()
{
    Login login;
    login.setMainWindow(this);
    if(login.exec() == QDialog::Rejected)
    {
        return false;
    }
    QDir dir;
    dir.mkpath("C:/LaQua/log/" + currentUserName());
    theApp->setLogFilePath(
                "C:/LaQua/log/"
                + currentUserName() + "/"
                + QDateTime::currentDateTime().toString("yyyy.MM.dd hh_mm_ss")
                + ".laquaLog.txt");


    qInfo() << "User name: " << currentUserName()
            << ",User rights: " << accessMode();
    this->show();

    qDebug("test");
    qWarning("test");
    qCritical("test");
    qInfo("test");
    return true;
}

void MainWindow::setCurrentUserName(const QString &currentUserName)
{
    m_currentUserName = currentUserName;
}

int MainWindow::accessMode() const
{
    return m_accessMode;
}

void MainWindow::setAccessMode(int accessMode)
{
    m_accessMode = accessMode;
}

QString MainWindow::currentUserName() const
{
    return m_currentUserName;
}

void MainWindow::navigate(QWidget *widget)
{
    Q_ASSERT(widget != NULL);

    QWidget *oldWidget = centralWidget();
    Widget *oldW = static_cast<Widget*>(oldWidget);
    if (oldW)
    {
        oldW->onExit();
    }

    //setCentralWidget(widget);

    Widget *newW = NULL;
    newW = static_cast<Widget*>(widget);
    if (newW)
    {
        newW->onEntry();
    }

}

void MainWindow::setCurrentWidget(QWidget *widget, bool isDelete)
{
    //qDebug() << m_stackedWidgetIsDelete.size();
    QWidget *currentWidget = m_stackedWidget->currentWidget();
    if (m_stackedWidgetIsDelete.contains(currentWidget) &&
            m_stackedWidgetIsDelete.value(currentWidget))
    {
        m_stackedWidget->removeWidget(currentWidget);
        m_stackedWidgetIsDelete.remove(currentWidget);
        delete currentWidget;
    }

    m_stackedWidget->addWidget(widget);
    m_stackedWidget->setCurrentWidget(widget);
    m_stackedWidgetIsDelete[widget] = isDelete;
}
