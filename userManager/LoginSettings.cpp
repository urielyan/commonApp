#include "LoginSettings.h"

LoginSettings::LoginSettings()
    : Settings()
    , m_userName("admin")
    , m_passwd("admin")
    , m_isSaved(false)
{

}

QString LoginSettings::userName() const
{
    return m_userName;
}

void LoginSettings::setUserName(const QString &userName)
{
    if (m_userName == userName)
    {
        emit userNameChanged();
        m_userName = userName;
    }
}

void LoginSettings::resetUserName()
{
    m_userName = "admin";
}

QString LoginSettings::passwd() const
{
    return m_passwd;
}

void LoginSettings::setPasswd(const QString &passwd)
{
    if (m_passwd == passwd)
    {
        m_passwd = passwd;
        emit passwdChanged();
    }
}

void LoginSettings::resetPasswd()
{
    m_userName = "admin";
}

bool LoginSettings::isSaved() const
{
    return m_isSaved;
}

void LoginSettings::setIsSaved(bool isSaved)
{
    if (m_isSaved == isSaved)
    {
        m_isSaved = isSaved;
        emit isSavedChanged();
    }
}

void LoginSettings::resetIsSaved()
{
    m_isSaved = false;
}
