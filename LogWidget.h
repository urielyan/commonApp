/*-------------------------------------------------------------------------------
文件名称：LogWidget.h
文件描述：从文件中读取日志并显示出来，日志为MessageHandle.h中定义的函数。
        在App中 qInstallMessageHandler(myMessageOutput);
备    注：
作者   ：闫葛
完成日期：2019.1.16
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include "Widget.h"

#include <QWidget>

namespace Ui {
class LogWidget;
}

class QStandardItemModel;
class LogWidget : public Widget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

    void fromFile(QString path);
    void initLogSelector(QString dirPath);

private slots:
    void on_messageType_activated(int index);

    void on_logSelector_currentIndexChanged(const QString &arg1);

private:
    Ui::LogWidget *ui;
    QStandardItemModel *m_model;
    QString m_logDirPath;
};

#endif // LOGWIDGET_H
