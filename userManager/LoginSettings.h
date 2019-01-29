#ifndef LOGINSETTINGS_H
#define LOGINSETTINGS_H

#include <QObject>
#include <Settings.h>

class LoginSettings : public Settings
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString passwd READ passwd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(bool isSaved READ isSaved WRITE setIsSaved NOTIFY isSavedChanged)
public:
    explicit LoginSettings();

    QString userName() const;
    void setUserName(const QString &userName);
    void resetUserName();

    QString passwd() const;
    void setPasswd(const QString &passwd);
    void resetPasswd();

    bool isSaved() const;
    void setIsSaved(bool isSaved);
    void resetIsSaved();

signals:
    void userNameChanged();
    void passwdChanged();
    void isSavedChanged();

public slots:

private:
    QString m_userName;
    QString m_passwd;
    bool m_isSaved;
};

#endif // LOGINSETTINGS_H
