#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DataBaseManager;
class QActionGroup;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    static MainWindow* instance();

    DataBaseManager *database() const;
    void setDatabase(DataBaseManager *database);

    QString currentUserName() const;
    void setCurrentUserName(const QString &currentUserName);

    int accessMode() const;
    void setAccessMode(int accessMode);

public slots:
    void navigate(QWidget *widget);

protected:
    static MainWindow *s_instance;
    QString m_currentUserName;
    DataBaseManager *m_databaseManager;
    int m_accessMode;

};

#endif // MAINWINDOW_H
