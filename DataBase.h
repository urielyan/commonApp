/*-------------------------------------------------------------------------------
文件名称：DataBase.h
文件描述：数据库管理软件
备    注：采用SQlite数据库。
作者   ：闫葛
完成日期：2018.10.10
修改日期：每次修改请注明修改内容和日期

---------------------------------------------------------------------------------*/
#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QObject>


#define ALLDATA_ID "id"
#define ALLDATA_DATETIME "dateTime"
#define ALLDATA_SPEED "speed"

#define USER_USERNAME "userName"
#define USER_PASSWD "passwd"
#define USER_ACCESSMODE "accessMode"


class QSqlTableModel;
class QSqlDatabase;
class QSqlQueryModel;
class QSqlRecord;
class DataBaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseManager(QObject *parent = 0);
    ~DataBaseManager();

    /**
     * @brief:
     * init 被调用之前需要设置 m_databaseName， m_connectionName， m_tableCount
     * 否则无法进行初始化
     *
     * @return
     * 成功返回true，否则false
     */
    bool init();
    QSqlDatabase *db() const;
    void setDb(QSqlDatabase *db);

    /**
     *  @brief: 得到数据库中的表以 QSqlTableModel 形式。
     *  @param: tableName： 表名。
     *  @return: 找到的model。
     */
    QSqlTableModel *model(QString tableName) const;

    /**
     *  @brief: 插入数据 dataList 到 表dataList中。
     *  @param: tableName：表名。
     *  @param: dataList：数据链表，必须以数据库中表数据一致。
     *  @return: 成功返回true，否则false。
     */
    bool saveDataToTable(QString tableName, QStringList dataList);
    bool saveDataToTable(QString tableName, QSqlRecord record);

    QString connectionName() const;
    void setConnectionName(const QString &connectionName);

    QString databaseName() const;
    void setDatabaseName(const QString &databaseName);

    int tableCount() const;
    void setTableCount(int tableCount);

    bool contains(QString tableName);

    QStringList tables() const;
    bool createTable(QString tableName, QString recordNames);
    bool createTable(QString tableName, QStringList recordNames);

signals:

public slots:

private:
    QString             m_databaseName;             //!< 数据库的名称，对sqlite来说就是文件名
    QString             m_connectionName;           //!< 数据库的连接名称

    QSqlDatabase*       m_db;                       //!< 对应的数据库指针
    int m_tableCount;                               //!< 共有多少个表，验证init函数是否正确初始化
    QMap<QString, QSqlTableModel*> m_tables;
};
#endif // DATABASE_H
