#include "UserData.h"
#include "DataBase.h"

#include "MainWindow.h"
#include "Widget.h"

#include <QDebug>
#include <QLabel>
#include <QStackedLayout>
#include <QStackedWidget>

MainWindow *MainWindow::s_instance = 0;
void MainWindow::initStackedWidget()
{
    this->setCentralWidget(m_stackedWidget);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_databaseManager(new DataBaseManager(this))
    , m_stackedWidget(new QStackedWidget(this))
{
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
