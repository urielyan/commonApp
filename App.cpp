#include "App.h"
#include "MessageHandle.h"
App::App(int& argc, char** argv)
    : QApplication(argc, argv)
    , m_mainWindow(NULL)

{
    showSplashMessage("test++++++++++++++");
}

bool App::init()
{
    qInstallMessageHandler(qtMessageHandler);
    //qInstallMessageHandler(myMessageOutput);

    /*
     * @brief 加载欢迎界面
     */
    qDebug("Loading splash-screen page ...");
    m_splash.setPixmap(QPixmap("resources/splash.jpg"));
    qDebug("Painting splash-screen page ...");
    m_splash.show();

    //设置全局字体
    setFont(QFont("Microsoft Yahei", 14, QFont::Bold));

    return true;
}


/*!
 * 在欢迎界面上显示文本信息，仅在初始化时使用
 * @param[in]  message 需要显示的文本信息
 */
void App::showSplashMessage(const QString& message)
{
    m_splash.showMessage(message, Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
    processEvents();
}
