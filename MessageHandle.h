#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include <QApplication>
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strMessage = strMsg + QString("%1, File:%2, Line:%3, Function:%4, DateTime:%5\n")
            .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);
    printf("%s", strMessage.toLocal8Bit().data());

    // 输出信息至文件中（读写、追加形式）
    QString fileName = QDateTime::currentDateTime().toString("yyyy.MM.dd hh_mm_ss") + ".laquaLog.txt";
    QFile file(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}


int visualStudioPrintf( const char* fmt, ... )
{
    va_list ap;
    int count = 0;

    va_start(ap, fmt);

#ifdef _MSC_VER
    static char szBuffer[4096];
    count = vsnprintf_s(szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0]), fmt, ap);

    //OutputDebugStringA(szBuffer);

    //输出到终端
#if defined _MSC_VER && defined _DEBUG && defined ENABLE_CONSOLE
    QString consoleOutString(szBuffer);
    WriteConsole(
        GetStdHandle(STD_OUTPUT_HANDLE),
        consoleOutString.unicode(), consoleOutString.size(),
        NULL, NULL
        );
#endif

#else
    vprintf(fmt, ap);
#endif

    va_end(ap);

    return count;
}


/*!
 * QT的消息handler，可以用于格式化打印信息等特殊操作
 */
void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char* localMsgData = localMsg.constData();
    switch (type) {
    case QtDebugMsg:
#ifdef _DEBUG
    case QtWarningMsg:
    case QtCriticalMsg:
#endif
        visualStudioPrintf("%s\n", localMsgData);
        break;
#ifndef _DEBUG
    case QtWarningMsg:
        visualStudioPrintf("Warning: %s (%s:%u, %s)\n", localMsgData, context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        visualStudioPrintf("Critical: %s (%s:%u, %s)\n", localMsgData, context.file, context.line, context.function);
        break;
#endif
    case QtFatalMsg:
        visualStudioPrintf("Fatal: %s (%s:%u, %s)\n", localMsgData, context.file, context.line, context.function);
        if (!localMsg.isEmpty())
        {
            QString errorMessage;
            errorMessage = QString("Fatal: %1 (%2:%3, %4)").arg(msg).arg(context.file).arg(context.line).arg(context.function);
            //emit (static_cast<Application *>(qApp))->error(errorMessage);
        }
//        dump(0);
//        abort();
    }
}
#endif // MESSAGEHANDLE_H
