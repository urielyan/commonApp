#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QItemSelection>
#include <QWidget>
#include <Widget.h>

namespace Ui {
class UserManager;
}

class QSqlTableModel;
class UserManager : public Widget
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = 0);
    ~UserManager();

    QSqlTableModel *model() const;
    void setModel(QSqlTableModel *model);

protected:

private slots:

    void on_deleteSelectUser_clicked();

    void on_addUser_clicked();

    void on_altPasswd_clicked();

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    Ui::UserManager *ui;
    QSqlTableModel *m_model;
};

#endif // USERMANAGER_H
