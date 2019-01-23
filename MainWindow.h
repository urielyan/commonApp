/*-------------------------------------------------------------------------------
文件名称：MainWindow.h
文件描述：定义一个主界面基类，初始化数据库，用户权限（TODO），和界面导航。
        定义用户管理界面、日志管理界面
备    注：
作者   ：闫葛
完成日期：2018.05.10
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class DataBaseManager;
class QActionGroup;
class QStackedLayout;
class QStackedWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    static MainWindow* instance();

    DataBaseManager *database() const;
    void setDatabase(DataBaseManager *database);

    bool login();
    QString currentUserName() const;
    void setCurrentUserName(const QString &currentUserName);

    int accessMode() const;
    void setAccessMode(int accessMode);

public slots:
    void navigate(QWidget *widget);
    void setCurrentWidget(QWidget *widget, bool isDelete = false);

protected:
    void initStackedWidget();

    /**
     * @brief 对于普通软件来说，需要添加的模块，目前添加了用户管理，日志管理
     * @param[in]
     * @return
     * @note
     */
    void initUserManagerWidget();
    void initDataBaseManager(QString dbPath);

protected slots:
    virtual void userManaggerActionClicked();
    virtual void openLogActionClicked();
protected:
    static MainWindow *s_instance;
    QString m_currentUserName;
    DataBaseManager *m_databaseManager;
    int m_accessMode;

    QStackedWidget *m_stackedWidget;
    QMap<QWidget*, bool> m_stackedWidgetIsDelete;

private:
    void setCentralWidget(QWidget *widget)
    {
        QMainWindow::setCentralWidget(widget);
    }

};

#endif // MAINWINDOW_H
