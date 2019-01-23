#include "App.h"
#include "MessageHandle.h"

#include <QTextCodec>
App::App(int& argc, char** argv)
    : QApplication(argc, argv)
    , m_mainWindow(NULL)
    , m_logFilePath("")

{
    showSplashMessage("test++++++++++++++");
}

bool App::init()
{
    //qInstallMessageHandler(myMessageOutput);
    qInstallMessageHandler(myMessageOutput);

    /*
     * @brief 加载欢迎界面
     */
    //qDebug("Loading splash-screen page ...");
    m_splash.setPixmap(QPixmap(":/images/DemoBackground.jpg"));
    //qDebug("Painting splash-screen page ...");
    //m_splash.show();

    //设置全局字体
    setFont(QFont("Microsoft Yahei", 14, QFont::Bold));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName( "utf8" ) );
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

void App::setLogFilePath(const QString &logFilePath)
{
    m_logFilePath = logFilePath;
}

QString App::logFilePath() const
{
    return m_logFilePath;
}
