#include "mainwindow.h"
#include <QApplication>
#include "centralairconditioner.h"
#include "databasecontrol.h"
#include "client.h"

centralAirConditioner airConditioner ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;


    QObject::connect(w,SIGNAL(TimeStartSignal()),&airConditioner, SLOT(TimeStart()));
    QObject::connect(w,SIGNAL(TimeStopSignal()),&airConditioner,SLOT(TimeStop()));

    client *x = new client;
    QObject::connect(w, SIGNAL(DataLogin(QString, QString)), x, SLOT(Login(QString, QString)));
    QObject::connect(x, SIGNAL(TransMainWindow(int, int, int)), &airConditioner, SLOT(RevState(int, int, int)));
    QObject::connect(x, SIGNAL(RefreshCost(QString, QString)), &airConditioner, SLOT(RevCost(QString, QString)));
    QObject::connect(&airConditioner, SIGNAL(SignalRequestEnd()), x, SLOT(SendRequestEnd()));
    QObject::connect(&airConditioner, SIGNAL(SignalRequest()), x, SLOT(SendRequest()));
    QObject::connect(x, SIGNAL(SignalChangeTemperature()), &airConditioner, SLOT(ChangeTemperature()));
    QObject::connect(x, SIGNAL(SignalChangeBlowSpeed()), &airConditioner, SLOT(ChangeBlowSpeed()));
    //databaseControl database;

    w->show();

    return a.exec();
}
