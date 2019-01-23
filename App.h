#ifndef APP_H
#define APP_H

#include "MainWindow.h"

#include <QApplication>
#include <QObject>
#include <QSplashScreen>

class App : public QApplication
{
    Q_OBJECT
public:
    /*!
     * 构造函数
     * @param[in]    argc
     * @param[in]    argv
     */
    App(int& argc, char** argv);

    /*!
     * 初始化整个系统，创建各个单例模式对象
     * 注意在此函数中仍可通过this->arguments()获取main函数传入的argv，
     * 并可通过此方式将初始化代码移动至此函数，
     * 从而保持main函数的整洁。
     * @return       操作成功返回true
     */
    virtual bool init();
    QString logFilePath() const;
    void setLogFilePath(const QString &logFilePath);

signals:

public slots:


private:
    MainWindow*         m_mainWindow;       //!< 全局唯一的主窗口对象
    QSplashScreen       m_splash;           //!< 欢迎界面

private:
    void showSplashMessage(const QString &message);
    QString m_logFilePath;
};

#if defined(theApp)
#undef theApp
#endif
#define theApp (static_cast<App *>(QApplication::instance()))

#endif // APP_H
