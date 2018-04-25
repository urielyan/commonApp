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
