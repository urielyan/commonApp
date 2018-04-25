#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QWidget>

namespace Ui {
class Login;
}

class MainWindow;
class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    MainWindow *mainWindow() const;
    void setMainWindow(MainWindow *mainWindow);
    bool isLogin();


private slots:

    void on_login_clicked();

    void on_quit_clicked();

private:
    Ui::Login *ui;

    MainWindow *m_mainWindow;
};

#endif // LOGIN_H
