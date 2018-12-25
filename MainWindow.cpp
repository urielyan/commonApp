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

#include "UserManager.h"

MainWindow *MainWindow::s_instance = 0;
void MainWindow::initStackedWidget()
{
    this->setCentralWidget(m_stackedWidget);
}

void MainWindow::initUserManagerWidget()
{
    QAction *userManagerAction = new QAction(tr("用户管理"), this);
    //this->addAction(userManagerAction);
    //this->menuBar()->addAction(userManagerAction);
    QMenu *userMenu = new QMenu(tr("帮助"),this);
    userMenu->addAction(userManagerAction);
    this->menuBar()->addMenu(userMenu);
    //this->
    connect(userManagerAction, &QAction::triggered,
            this, &MainWindow::userManaggerActionClicked);
}

void MainWindow::initDataBaseManager(QString dbPath)
{
    qDebug() <<  "+++Set DB Path+++" << dbPath;
    Q_ASSERT(QFile(dbPath).exists());
    m_databaseManager->setDatabaseName(dbPath);
    m_databaseManager->setConnectionName(QApplication::applicationName());
    //m_databaseManager->setTableCount(1);
    Q_ASSERT(m_databaseManager->init() == true);
    qDebug() << m_databaseManager->tables();
}

void MainWindow::userManaggerActionClicked()
{
    qDebug() << "test";
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_databaseManager(new DataBaseManager(this))
    , m_stackedWidget(new QStackedWidget(this))
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
        qDebug() << "MainWindow instance";
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
    qDebug() << m_stackedWidgetIsDelete.size();
     qDebug() << "test";
    QWidget *currentWidget = m_stackedWidget->currentWidget();
    if (m_stackedWidgetIsDelete.contains(currentWidget) &&
            m_stackedWidgetIsDelete.value(currentWidget))
    {
        m_stackedWidget->removeWidget(currentWidget);
        m_stackedWidgetIsDelete.remove(currentWidget);
        delete currentWidget;
    }
    qDebug() << "test";

    m_stackedWidget->addWidget(widget);
    m_stackedWidget->setCurrentWidget(widget);
    m_stackedWidgetIsDelete[widget] = isDelete;
}
