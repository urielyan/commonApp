#ifndef ALTERPASSWD_H
#define ALTERPASSWD_H

#include <QDialog>

namespace Ui {
class AlterPasswdDialog;
}

class AlterPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlterPasswdDialog(QWidget *parent = 0);
    ~AlterPasswdDialog();

    void setOldPasswd(QString oldPasswd);
    QString getNewPasswd();

private slots:
    void on_cancel_clicked();

    void on_sure_clicked();

private:
    Ui::AlterPasswdDialog *ui;
    QString m_oldPasswd;
};

#endif // ALTERPASSWD_H
