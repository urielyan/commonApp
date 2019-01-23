#include "SystemSettings.h"

#include <QSettings>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#define GET_SETTINGS(key, defaultValue) \
    QString currentAppDir = SystemSettings::getCurrentAppDir();\
    QString settingsFile = currentAppDir.append("/Settings.ini");\
    QSettings settings(settingsFile, QSettings::IniFormat);\
    if(!settings.contains(key))\
    {\
        settings.setValue(key, defaultValue);\
    }\
    QVariant value = settings.value(key, defaultValue);\

#define SET_SETTINGS(key, value) \
    QString currentAppDir = SystemSettings::getCurrentAppDir();\
    QString settingsFile = currentAppDir.append("/Settings.ini");\
    QSettings settings(settingsFile, QSettings::IniFormat);\
    settings.setValue(key, value);\

SystemSettings::SystemSettings(QObject *parent)
    : QObject(parent)
{

}

QVariant SystemSettings::getSettings(QString key, QVariant defaultValue)
{
    GET_SETTINGS(key, QVariant(defaultValue));
    return value;
}

void SystemSettings::setSettings(QString key, QVariant value)
{
    SET_SETTINGS(key, value);
}

bool SystemSettings::contains(const QString &key)
{
    QString currentAppDir = SystemSettings::getCurrentAppDir();\
    QString settingsFile = currentAppDir.append("/Settings.ini");\
    QSettings settings(settingsFile, QSettings::IniFormat);\
    if(!settings.contains(key))\
    {\
        return false;
    }

    return true;
}

QString SystemSettings::getCurrentAppDir()
{
    QApplication *a = qobject_cast<QApplication*>(QApplication::instance());
    QString exeFile = a->applicationDirPath();
    //qDebug() << a->applicationDirPath() << a->applicationFilePath() << a->applicationDisplayName() << a->applicationVersion();
    QFileInfo fileInfo(exeFile);
    QString appDir = fileInfo.absoluteFilePath();

    //qDebug() << __FUNCTION__ << appDir;
    return appDir;
}

uint SystemSettings::getPort()
{
    GET_SETTINGS("UdpPort", 6000);
    return value.toUInt();
}

void SystemSettings::setIP(QString ip)
{
    SET_SETTINGS("IP", ip);
}

QString SystemSettings::getIP()
{
    GET_SETTINGS("IP", "192.168.0.2");
    return value.toString();
}
