#ifndef INCLUDES_H
#define INCLUDES_H

#include "MainWindow.h"
#define MAINWINDOW MainWindow::instance()

#include <QDebug>
#define PRINT_ERR (qDebug() \
    <<"file: " << __FILE__ << ";  " \
    << "funcion: " << __FUNCTION__ << ";  " \
    << "line: " << __LINE__ << ";  " \
    );

#define DATETIME_FORMATE "yyyy/MM/dd hh:mm:ss"

#endif // INCLUDES_H
