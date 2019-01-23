/*-------------------------------------------------------------------------------
文件名称：Widget.h
文件描述：所有界面的基类。重新定义QWidget，以便添加自己的接口。
备    注：
作者   ：闫葛
完成日期：
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    virtual void onEntry();
    virtual void onExit();

signals:
    void navigate(QWidget *widget);

public slots:
};

#endif // WIDGET_H
