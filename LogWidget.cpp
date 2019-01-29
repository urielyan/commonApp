#include "LogWidget.h"
#include "ui_LogWidget.h"

#include <QFile>
#include <QStandardItemModel>
#include <QDebug>
#include <QDir>

LogWidget::LogWidget(QWidget *parent) :
    Widget(parent),
    ui(new Ui::LogWidget)
  , m_model(new QStandardItemModel(this))

{
    ui->setupUi(this);
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::fromFile(QString path)
{
    m_model->clear();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int row = 0;
    m_model->setColumnCount(6);
    QString allLog = QString(file.readAll());
    QStringList logs = allLog.split("<@>");
    for (int i = 0; i < logs.size(); ++i)
    {
        QStringList aLogs = logs.value(i).trimmed().split("<!>");
        //qDebug() << aLogs << "\n\n";

        if (aLogs.size() == m_model->columnCount())
        {
            m_model->setRowCount(++row);
            for (int i = 0; i < m_model->columnCount(); ++i) {
                QStandardItem *item = new QStandardItem(
                            QString(aLogs.value(i))
                            );
                m_model->setItem(row - 1, i, item);
            }
        }
    }

    ui->tableView->setModel(m_model);
    m_model->setHeaderData(0, Qt::Horizontal, "种类");
    m_model->setHeaderData(1, Qt::Horizontal, "内容");
    m_model->setHeaderData(2, Qt::Horizontal, "文件");
    m_model->setHeaderData(3, Qt::Horizontal, "行数");
    m_model->setHeaderData(4, Qt::Horizontal, "函数");
    m_model->setHeaderData(5, Qt::Horizontal, "日期");

    ui->tableView->resizeColumnsToContents();
}

void LogWidget::initLogSelector(QString dirPath)
{
    QDir dir(dirPath);
    m_logDirPath = dirPath;
    ui->logSelector->addItems(dir.entryList(QStringList("*.laquaLog.txt"))) ;
}

void LogWidget::on_messageType_activated(int index)
{
    QString strMsg("all");
    switch(index -1)
    {
    case QtDebugMsg:
        strMsg = QString("Debug");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical");
        break;
    case QtInfoMsg:
        strMsg = QString("Info");
        break;
    }

    //qDebug() << strMsg << QtDebugMsg << QtWarningMsg << QtCriticalMsg << QtFatalMsg << index;
    for (int i = 0; i < ui->tableView->model()->rowCount(); ++ i)
    {
        if (index == 0)
        {
            ui->tableView->showRow(i);
            continue;
        }

        ui->tableView->hideRow(i);
        QModelIndex modelIndex =  ui->tableView->model()->index(i, 0);
        if (modelIndex.isValid() && modelIndex.data().toString().contains(strMsg))
        {
            ui->tableView->showRow(i);
        }
    }

}

void LogWidget::on_logSelector_currentIndexChanged(const QString &arg1)
{
    fromFile(m_logDirPath + "/" + arg1);
}
