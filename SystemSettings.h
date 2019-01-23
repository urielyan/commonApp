/*-------------------------------------------------------------------------------
文件名称：SystemSettings.h
文件描述：简易系统配置保存类，通过字符串的方式保存配置到固定文件中。
备    注：适合小项目，大项目请用Settings类。
作者   ：闫葛
完成日期：2017.05.06
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef SYSTEMTRANSPLANTATION_H
#define SYSTEMTRANSPLANTATION_H

#include <QObject>
#include <QVariant>

#define IP_KEY "IP"

class SystemSettings : public QObject
{
    Q_OBJECT
public:
    explicit SystemSettings(QObject *parent = 0);

    static QVariant getSettings(QString key, QVariant defaultValue = QVariant(""));
    static void setSettings(QString key, QVariant value);
    static bool contains(const QString &key);

    static QString getCurrentAppDir();
    static uint getPort();

    static void setIP(QString ip);
    static QString getIP();
signals:

public slots:

private:
};

#endif // SYSTEMTRANSPLANTATION_H
