#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class DataBaseManager;
class QActionGroup;
class QStackedLayout;
class QStackedWidget;
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
    void setCurrentWidget(QWidget *widget, bool isDelete = false);

protected:
    void initStackedWidget();

protected:
    static MainWindow *s_instance;
    QString m_currentUserName;
    DataBaseManager *m_databaseManager;
    int m_accessMode;

    QStackedWidget *m_stackedWidget;
    QMap<QWidget*, bool> m_stackedWidgetIsDelete;
};

#endif // MAINWINDOW_H
