#include "DataBase.h"
//#include "Defines.h"

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
    qDebug() << __FILE__ << __LINE__;
}

bool DataBaseManager::init()
{
    //return false;
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", m_connectionName));

    m_db->setDatabaseName(m_databaseName);

    if(m_db->open())
    {
        //判断表是否存在，若不存在，则执行建表操作
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
        qDebug() << m_db->lastError().text() << QFile(m_databaseName).exists();
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
    Q_ASSERT(m_tables.contains(tableName));
    return m_tables.value(tableName, new QSqlTableModel());
}

bool DataBaseManager::saveDataToTable(QString tableName, QStringList dataList)
{
    Q_ASSERT(m_tables.contains(tableName));

    QSqlTableModel *model = m_tables.value(tableName);
    QSqlRecord record = model->record();

    Q_ASSERT(dataList.size() == record.count());

    for (int i = 0; i < dataList.size(); ++i)
    {
        record.setValue(i, dataList.value(i));
    }

    bool isInsert = model->insertRecord(0, record);
    if(isInsert == false)
    {
        qDebug() << model->lastError().text();
    }
    model->submitAll();

    return true;
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
