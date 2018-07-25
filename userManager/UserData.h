#ifndef USERDATA_H
#define USERDATA_H

#include "includes.h"
#include <QObject>
#include <QSqlRecord>

class UserData : public QObject
{
    Q_OBJECT
    Q_ENUMS(AccessMode)
public:
    enum AccessMode
    {
        None = 0,       //!< 无权限
        Guest = 1,      //!< 游客
        User = 2,       //!< 普通用户
        Admin = 3,      //!< 管理员
        Root = 4,      //!< 管理员
    };

    enum Gender
    {
        Male = 0,
        Female
    };

    explicit UserData(QObject *parent = 0);

    QString userName() const;
    void setUserName(const QString &userName);

    QString passwd() const;
    void setPasswd(const QString &passwd);

    QSqlRecord toSqlRecord();
    QStringList getAccessList();

    int getGender() const;
    void setGender(const int &gender);

    int getAge() const;
    void setAge(int age);

    double getWeight() const;
    void setWeight(double weight);

    double getStature() const;
    void setStature(double stature);

    int access() const;
    void setAccess(int access);

signals:

public slots:

private:
    QString m_userName;
    QString m_passwd;
    Gender m_gender;
    int m_age;
    double m_weight;
    double m_stature;
    int m_access;
};

#endif // USERDATA_H
