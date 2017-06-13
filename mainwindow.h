#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QAction>
#include <QPushButton>
#include <ui_dialoguserregister.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool UserRegister();
    void ShowWidgetMain();
    QString GetBlowSpeedString(int);
    int GetBlowSpeedNum(const QString &);
    int GetWorkModelNum(const QString&);
    QString GetWorkModelString(const int&);

public slots:
    void Refresh();

private slots:
    void Init();
    //void PushButtonStartClicked();
    void SendSignalLogout();
    void ShowMsgLogout();
    //void ChangeWorkTemperature();


    void OnPushButtonStartClicked();

    void on_comboBoxModel_currentIndexChanged(const QString &arg1);

    void on_comboBoxBlowSpeed_currentIndexChanged(const QString &arg1);

    void on_spinBoxTemperature_valueChanged(int arg1);

signals:
    void TimeStartSignal();
    void TimeStopSignal();
    void DataLogin(QString, QString);
    void SignalLogout();
    void valueChangedF(const float &);


private:
    Ui::Dialog *uiDialog;
    Ui::MainWindow *ui;
    QDialog *dialog;
    QTimer *timeRefresh;

    int clickMux;
};

#endif // MAINWINDOW_H
