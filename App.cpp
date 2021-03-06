#include "App.h"
#include "MessageHandle.h"
#include "Settings.h"

#include <QTextCodec>
App::App(int& argc, char** argv)
    : QApplication(argc, argv)
    , m_mainWindow(NULL)
    , m_logFilePath("")
    , m_settingsManager(new SettingsManager)
{
    showSplashMessage("test++++++++++++++");
}

bool App::init()
{
    //设置字体编码和字体
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
    //设置全局字体
    setFont(QFont("Microsoft Yahei", 14, QFont::Bold));

    //qInstallMessageHandler(myMessageOutput);
    //TODO: qInstallMessageHandler(myMessageOutput);

    /*
     * @brief 加载欢迎界面
     */
    //qDebug("Loading splash-screen page ...");
    m_splash.setPixmap(QPixmap(":/images/DemoBackground.jpg"));
    //qDebug("Painting splash-screen page ...");
    //m_splash.show();


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

SettingsManager* App::settingsManager() const
{
    return m_settingsManager;
}

void App::saveSettings()
{
    m_settingsManager->save("C:/LaQua/profile/default.ini");
}

void App::loadSettings()
{
    m_settingsManager->load("C:/LaQua/profile/default.ini");
}

QString App::logFilePath() const
{
    return m_logFilePath;
}
