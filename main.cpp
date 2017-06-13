#include "mainwindow.h"
#include <QApplication>
#include "centralairconditioner.h"
#include "databasecontrol.h"
#include "client.h"

centralAirConditioner airConditioner ;
int checkConnect;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client *x = new client;
    MainWindow *w= new MainWindow;;

    checkConnect = 0;
    //QThread *thread = new QThread(x);
    //x->moveToThread(thread);
    //thread->start();
    QObject::connect(&airConditioner, SIGNAL(SignalInit()), w, SLOT(Init()));
    //bool isConnected;
    QObject::connect(w, SIGNAL(DataLogin(QString, QString)), x, SLOT(Login(QString, QString)),Qt::DirectConnection);
    //qDebug() << "isConnected:" << isConnected;

    QObject::connect(x, SIGNAL(TransMainWindow(int, float, float)), &airConditioner, SLOT(RevState(int, float, float)));
    QObject::connect(x, SIGNAL(RefreshCost(QString, QString)), &airConditioner, SLOT(RevCost(QString, QString)));
    QObject::connect(&airConditioner, SIGNAL(SignalRequestEnd()), x, SLOT(SendRequestEnd()));
    //明明只连接了一次，但为什么槽函数却执行了多次呢？


    //QObject::connect(&airConditioner, SIGNAL(SignalRequest()), x, SLOT(SendRequest()));
    QObject::disconnect(&airConditioner, &centralAirConditioner::SignalRequest, x, &client::SendRequest);
    QObject::connect(&airConditioner, &centralAirConditioner::SignalRequest, x, &client::SendRequest, Qt::UniqueConnection);
    qDebug() << "connect how many times";
   // QObject::connect(&airConditioner, &centralAirConditioner::SignalRequest, x, &client::SendRequest, Qt::UniqueConnection);
    //qDebug() << "connect how many times";
    QObject::connect(&airConditioner, SIGNAL(SignalBlowSpeed()), x, SLOT(SendBlowSpeed()));

    QObject::connect(x, SIGNAL(SignalChangeTemperature()), &airConditioner, SLOT(ChangeTemperature()));
    QObject::connect(x, SIGNAL(SignalChangeBlowSpeed()), &airConditioner, SLOT(ChangeBlowSpeed()));
    //databaseControl database;
    QObject::connect(w, SIGNAL(SignalLogout()), x, SLOT(Logout()));
    QObject::connect(x, SIGNAL(SignalRefresh()), w, SLOT(Refresh()));

    if(!w->UserRegister())
    {
        w->close();
        //this->hide();
        //待修正关闭事件
    }
    //w->Init();
    //qDebug() << "test";
    w->show();
    w->ShowWidgetMain();
    return a.exec();
}
