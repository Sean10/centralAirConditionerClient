#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDateTime>
#include <QTimer>
//#include <QObject>

//class centralAirConditioner;
//centralAirConditioner *airConditioner;


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

public slots:
    void Refresh();

private slots:
    void PushButtonStartClicked();

signals:
    void TimeStartSignal();
    void TimeStopSignal();

private:
    Ui::MainWindow *ui;
    QTimer *timeRefresh;
};

#endif // MAINWINDOW_H
