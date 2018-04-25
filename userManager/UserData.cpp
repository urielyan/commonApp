#include "UserData.h"

#include <QSqlField>
#include <QMetaEnum>
#include <QDebug>

UserData::UserData(QObject *parent)
    : QObject(parent)
    , m_userName("")
    , m_passwd("")
    , m_access(0)
{
}

QString UserData::userName() const
{
    return m_userName;
}

void UserData::setUserName(const QString &userName)
{
    m_userName = userName;
}

QString UserData::passwd() const
{
    return m_passwd;
}

void UserData::setPasswd(const QString &passwd)
{
    m_passwd = passwd;
}

QSqlRecord UserData::toSqlRecord()
{
    QSqlRecord record;
    record.append(QSqlField("userName", QVariant::Double));
    record.append(QSqlField("passwd", QVariant::String));
    record.append(QSqlField("accessMode", QVariant::Int));
    record.append(QSqlField("gender", QVariant::Bool));
    record.append(QSqlField("age", QVariant::Int));
    record.append(QSqlField("weight", QVariant::Double));
    record.append(QSqlField("stature", QVariant::Double));

    record.setValue("userName", m_userName);
    record.setValue("passwd", m_passwd);
    record.setValue("accessMode", m_access);
    record.setValue("gender", m_gender);
    record.setValue("age", m_age);
    record.setValue("weight", m_weight);
    record.setValue("stature", m_stature);

    return record;
}

QStringList UserData::getAccessList()
{
    QStringList strList;
    //this->metaObject()->enumerator(0).key(1);
    for (int i = 0; i <= Admin; ++i)
    {
        strList.append(this->metaObject()->enumerator(0).key(i));
    }

    return strList;
}

int UserData::getGender() const
{
    return m_gender;
}

void UserData::setGender(const int &gender)
{
    if(gender == Male)
    {
        m_gender = Male;
    }else
    {
        m_gender = Female;
    }
}

int UserData::getAge() const
{
    return m_age;
}

void UserData::setAge(int age)
{
    m_age = age;
}

double UserData::getWeight() const
{
    return m_weight;
}

void UserData::setWeight(double weight)
{
    m_weight = weight;
}

double UserData::getStature() const
{
    return m_stature;
}

void UserData::setStature(double stature)
{
    m_stature = stature;
}


int UserData::access() const
{
    return m_access;
}

void UserData::setAccess(int access)
{
    m_access = access;
}
