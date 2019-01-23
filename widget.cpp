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
    //qDebug() <<"Entry:" << this->objectName();
}

void Widget::onExit()
{
    //qDebug() <<"Exit:" << this->objectName();
}
