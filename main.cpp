#include "mainwindow.h"
#include <QApplication>
#include "centralairconditioner.h"

centralAirConditioner airConditioner ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    //refreshThread *threadRefresh = new refreshThread;

    QObject::connect(w,SIGNAL(TimeStartSignal()),&airConditioner, SLOT(TimeStart()));
    QObject::connect(w,SIGNAL(TimeStopSignal()),&airConditioner,SLOT(TimeStop()));
   // QObject::connect(threadRefresh, SIGNAL(SignaRefresh()), w, SLOT(refresh()));

    w->show();
   // threadRefresh->start();


    return a.exec();
}
