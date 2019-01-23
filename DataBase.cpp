#include "DataBase.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QTableView>

#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject(parent)
    , m_db(NULL)
    , m_tableCount(0)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        QMessageBox::critical(NULL, "Unable to load database", "This demo needs the SQLITE driver");
    }
}

DataBaseManager::~DataBaseManager()
{
    if (m_db)
    {
        delete m_db;
        m_db = NULL;
    }
}

bool DataBaseManager::init()
{
    //return false;
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", m_connectionName));

    m_db->setDatabaseName(m_databaseName);

    if(m_db->open())
    {
        foreach (QString table, m_db->tables()) {
            QSqlTableModel * model= new QSqlTableModel(this, *m_db);
            model->setTable(table);
            model->select();
            m_tables[table] = model;
        }

        return true;
    }
    else
    {
        qWarning() << QStringLiteral("数据库初始化错误：") << m_db->lastError().text();
    }

    return false;
}

QSqlDatabase *DataBaseManager::db() const
{
    return m_db;
}

void DataBaseManager::setDb(QSqlDatabase *db)
{
    m_db = db;
}

QSqlTableModel *DataBaseManager::model(QString tableName) const
{
    //qDebug() << tableName;
    Q_ASSERT(m_tables.contains(tableName));
    return m_tables.value(tableName, new QSqlTableModel());
}

bool DataBaseManager::saveDataToTable(QString tableName, QStringList dataList)
{
    //quint64 dateTime = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << "-----start" << dateTime;
    Q_ASSERT(m_tables.contains(tableName));
    QString values;
    foreach (QString str, dataList) {
        values.append("\'");
        values.append(str);
        values.append("\'");
        values.append(", ");
    }
    values.chop(2);
    //qDebug() << QDateTime::currentMSecsSinceEpoch() - dateTime;

    QSqlQuery query(*m_db);
    //qDebug() << QDateTime::currentMSecsSinceEpoch() - dateTime;
    QString insertTable =     QString(
                "insert into '%1' values(%2)")
            .arg(tableName).arg(values);
    //qDebug() << insertTable;
    if (!query.exec(insertTable))
    {
        //qDebug() << query.lastError();
        return false;
    }
    //qDebug() << QDateTime::currentMSecsSinceEpoch() - dateTime;

    return true;

//    QSqlTableModel *model = m_tables.value(tableName);
    QSqlTableModel model(this, *m_db);
    model.setTable(tableName);
    //qDebug() <<model.lastError();
    model.select();
    QSqlRecord record = model.record();
    //qDebug() << m_db->tables();


    //qDebug() << dataList.size() <<  record.count() << tableName;
    Q_ASSERT(dataList.size() == record.count());

    for (int i = 0; i < dataList.size(); ++i)
    {
        record.setValue(i, dataList.value(i));
    }

    bool isInsert = model.insertRecord(0, record);
    if(isInsert == false)
    {
        qWarning() << QStringLiteral("数据保存错误：") << model.lastError().text();
    }
    model.submitAll();

    return true;
}

bool DataBaseManager::saveDataToTable(QString tableName, QSqlRecord record)
{
    //qDebug() << m_tables;
    Q_ASSERT(m_tables.contains(tableName));
    QSqlTableModel *model = m_tables.value(tableName);

    bool isInsert = model->insertRecord(0, record);
    if(isInsert == false)
    {
        qDebug() << ( QStringLiteral("Database save data error：") + model->lastError().text());
    }
    model->submitAll();

    return isInsert;
}

QString DataBaseManager::connectionName() const
{
    return m_connectionName;
}

void DataBaseManager::setConnectionName(const QString &connectionName)
{
    m_connectionName = connectionName;
}

QString DataBaseManager::databaseName() const
{
    return m_databaseName;
}

void DataBaseManager::setDatabaseName(const QString &databaseName)
{
    m_databaseName = databaseName;
}

int DataBaseManager::tableCount() const
{
    return m_tableCount;
}

void DataBaseManager::setTableCount(int tableCount)
{
    m_tableCount = tableCount;
}

bool DataBaseManager::contains(QString tableName)
{
    return m_tables.contains(tableName);
}

QStringList DataBaseManager::tables() const
{
    return m_tables.keys();
}

bool DataBaseManager::createTable(QString tableName, QString recordNames)
{
    QSqlQuery query(*m_db);

    QString createTable = QString(
        "create table '%1' (%2)"
        ).arg(tableName).arg(recordNames);
    //qDebug() << createTable;
    if (!query.exec(createTable))
    {
        return false;
    }

    QSqlTableModel * model= new QSqlTableModel(this, *m_db);
    model->setTable(tableName);
    model->select();
    m_tables[tableName] = model;
    return true;
}

bool DataBaseManager::createTable(QString tableName, QStringList recordNames)
{
    QString fields;

    foreach (QString str, recordNames) {
        fields.append(str);
        fields.append(" STRING, ");
    }
    fields.chop(2);

    return createTable(tableName, fields);
}
