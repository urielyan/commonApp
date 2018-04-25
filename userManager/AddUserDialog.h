#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "UserData.h"

namespace Ui {
class AddUser;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = 0);
    ~AddUserDialog();

    UserData* data() const;
    void setData(UserData *data);

private slots:
    void on_add_clicked();

    void on_cancel_clicked();

private:
    Ui::AddUser *ui;
    UserData *m_data;
};

#endif // ADDUSER_H
