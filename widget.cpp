#include "includes.h"
#include "Widget.h"

#include <QDebug>

#include "MainWindow.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &Widget::navigate, MAINWINDOW, &MainWindow::navigate);
}

Widget::~Widget()
{
    onExit();
}

void Widget::onEntry()
{
    qDebug() << this->objectName();
}

void Widget::onExit()
{
    qDebug() << this->objectName();
}
