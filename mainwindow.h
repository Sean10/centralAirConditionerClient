#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDateTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init();
    bool UserRegister();

public slots:
    void Refresh();

private slots:
    void PushButtonStartClicked();

signals:
    void TimeStartSignal();
    void TimeStopSignal();
    void DataLogin(QString, QString);

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
    QTimer *timeRefresh;

    int clickMux;
};

#endif // MAINWINDOW_H
