#include "AlterPasswdDialog.h"
#include "ui_AlterPasswdDialog.h"

#include <QMessageBox>

AlterPasswdDialog::AlterPasswdDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlterPasswdDialog)
    , m_oldPasswd("")
{
    ui->setupUi(this);
    this->setWindowTitle(tr("修改密码"));
}

AlterPasswdDialog::~AlterPasswdDialog()
{
    delete ui;
}

void AlterPasswdDialog::setOldPasswd(QString oldPasswd)
{
    m_oldPasswd = oldPasswd;
}

QString AlterPasswdDialog::getNewPasswd()
{
    return ui->newPasswd->text();
}

void AlterPasswdDialog::on_cancel_clicked()
{
    this->reject();
}

void AlterPasswdDialog::on_sure_clicked()
{
    QString title = tr("输入错误");
    if (ui->oldPasswd->text().size() == 0)
    {
        QMessageBox::warning(this, title, tr("请输入老密码！"));
        return;
    }
    if (ui->newPasswd->text().size() == 0)
    {
        QMessageBox::warning(this, title, tr("请输入新密码！"));
        return;
    }
    if (ui->newPasswd->text().size() == 0)
    {
        QMessageBox::warning(this, title, tr("请确认新密码！"));
        return;
    }

    if (ui->oldPasswd->text().compare(m_oldPasswd) != 0)
    {
        QMessageBox::warning(this, title, tr("请输入正确的老密码！"));
        return;
    }

    if (ui->newPasswd->text().compare(ui->confimPasswd->text()) != 0)
    {
        QMessageBox::warning(this, title, tr("两次密码输入不一致！"));
        return;
    }

    this->accept();
}
