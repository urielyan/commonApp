#include "UserData.h"
#include "DataBase.h"

#include "MainWindow.h"
#include "Widget.h"

#include <QDebug>

MainWindow *MainWindow::s_instance = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_databaseManager(new DataBaseManager(this))
{
}

MainWindow::~MainWindow()
{
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

    setCentralWidget(widget);

    Widget *newW = NULL;
    newW = static_cast<Widget*>(widget);
    if (newW)
    {
        newW->onEntry();
    }
}
