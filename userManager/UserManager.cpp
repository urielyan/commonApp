﻿#include "UserManager.h"
#include "ui_UserManager.h"
#include "AddUserDialog.h"
#include "AlterPasswdDialog.h"

#include <QSqlTableModel>
#include <QDebug>

UserManager::UserManager(QWidget *parent) :
    Widget(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSortingEnabled(true);
}

UserManager::~UserManager()
{
    delete ui;
}

void UserManager::on_deleteSelectUser_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexs = selectionModel->selectedIndexes();

    foreach (QModelIndex index, indexs) {
//        qDebug() <<index.row();
        m_model->removeRow(index.row());
    }

    m_model->submitAll();
    m_model->select();
}

void UserManager::on_addUser_clicked()
{
    AddUserDialog addUser;

    if (addUser.exec() == QDialog::Rejected)
    {
        return;
    }

    m_model->insertRecord(0, addUser.data()->toSqlRecord());

    qDebug() << m_model->submitAll();
    m_model->select();
}

QSqlTableModel *UserManager::model() const
{
    return m_model;
}

void UserManager::setModel(QSqlTableModel *model)
{
    ui->tableView->setModel(model);
    m_model = model;
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &UserManager::selectionChanged);
}

void UserManager::selectionChanged(const QItemSelection &selected, const QItemSelection &/*deselected*/)
{

    foreach (QModelIndex index, selected.indexes()) {
        //qDebug() << index.column() << index.row();
    }
}


void UserManager::on_altPasswd_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexs = selectionModel->selectedIndexes();

    if (indexs.size() != m_model->columnCount())
    {
        return;
    }

    AlterPasswdDialog alterPasswd;
    alterPasswd.setOldPasswd(indexs.value(1).data().toString());
    if (alterPasswd.exec() == QDialog::Rejected)
    {
        return;
    }

    m_model->setData(indexs.value(1), alterPasswd.getNewPasswd());

    qDebug() << m_model->submitAll();
    m_model->select();
}
