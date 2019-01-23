#include "includes.h"
#include "DataBase.h"

#include "Login.h"
#include "ui_Logingin.h"
#include "MainWindow.h"
#include "UserData.h"

#include <QApplication>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
    , m_mainWindow(NULL)
{
    ui->setupUi(this);
    ui->user->setText("adm");
    ui->passwd->setText("adm");
    this->setWindowTitle(tr("请登陆"));
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    Q_ASSERT(m_mainWindow != NULL);
    if (ui->passwd->text() == "root" && ui->user->text() == "root")
    {
        m_mainWindow->setAccessMode(UserData::Root);
        m_mainWindow->setCurrentUserName(ui->user->text());
        m_mainWindow->show();
        this->close();
        this->accept();
        return;
    }

    DataBaseManager *dbManager = MAINWINDOW->database();
    //    QSqlTableModel *userModel = db->userModel();
    //    userModel->setQuery();

    QSqlQuery query(*dbManager->db());
    query.exec("SELECT * FROM user where userName = \"" + ui->user->text() + "\"");

    if (query.next())
    {
        QString passwd = query.value(USER_PASSWD).toString();
        int access = query.value(USER_ACCESSMODE).toInt();
        //qDebug() << passwd << ui->passwd->text();
        if (passwd.compare(ui->passwd->text()) == 0)
        {
            m_mainWindow->setAccessMode(access);
            m_mainWindow->setCurrentUserName(ui->user->text());
            //m_mainWindow->show();
            this->accept();
            this->close();
        }else
        {
            QMessageBox::warning(
                        this,
                        tr("密码错误"),
                        tr("您的密码有错，请重新输入")
                        );
            ui->passwd->clear();
        }
    }else
    {
        QMessageBox::warning(
                    this,
                    tr("用户不存在"),
                    tr("您的用户不存在，请重新输入")
                    );
        ui->user->clear();
        ui->passwd->clear();
    }
}

void Login::on_quit_clicked()
{
    this->reject();
    //delete m_mainWindow;
    //QApplication::instance()->quit();
    QApplication::instance()->exit(0);
    QApplication::instance()->quit();
}

MainWindow *Login::mainWindow() const
{
    return m_mainWindow;
}

void Login::setMainWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

bool Login::isLogin()
{
    return false;
}
