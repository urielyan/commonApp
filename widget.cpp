#include "includes.h"
#include "Widget.h"

#include <QDebug>

#include "MainWindow.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &Widget::navigate, MAINWINDOW, &MainWindow::navigate);
}

void Widget::onEntry()
{
    //TODO
}

void Widget::onExit()
{
    //TODO
}
