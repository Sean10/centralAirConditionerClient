#include "client.h"
#include "centralairconditioner.h"

client::client(QObject *parent):
    QTcpServer (parent)
{
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(RevInitData()));

}

void client::Login(QString user, QString roomNum)
{
    socket->connectToHost("10.211.15.36", 6666);
    if (socket->waitForConnected(1000))
    {
        QString a = "clientMsg/"+roomNum+"/"+user;
        socket->write(a.toLatin1());
    }
    else
    {
        qDebug() << "socket timeout!";
    }
}

void client::RevInitData()
{
    QString data = socket->readAll();
    qDebug() << data;
    QStringList list = data.split('/');

    int workModel = QString(list[1]).toInt();
    float lowTem = QString(list[2]).toFloat();
    float highTem = QString(list[3]).toFloat();

    disconnect(socket, SIGNAL(readyRead()), this, SLOT(RevInitData()));
    connect(socket, SIGNAL(readRead()), this, SLOT(RevData()));
    emit TransMainWindow(workModel, lowTem, highTem);
}

void client::RevData()
{
    QString datas = socket->readAll();
    qDebug() << datas;
    QStringList list = datas.split("/");


    if(QString::compare(QString(list[0]),"cost")==0)
    {
        emit RefreshCost(QString(list[1]),QString(list[2]));
    }
    if(QString::compare(QString(list[0]),"request")==0)
    {
        QString a= "answer/"+QString::number(airConditioner.GetTemperature(), 'f', 2)+"/"+QString::number(airConditioner.GetWorkTemperature(), 'f', 2)\
                +"/"+QString::number(airConditioner.GetBlowSpeed(), 10);
        socket->write(a.toLatin1());
    }
    if(QString::compare(QString(list[0]),"answer")==0)
    {
        emit SignalChangeTemperature();
    }
    if(QString::compare(QString(list[0]),"acceptWind")==0)
    {
        emit SignalChangeBlowSpeed();
    }
}

void client::SendRequestEnd()
{
    QString a="requestEnd";
    socket->write(a.toLatin1());
}

void client::SendRequest()
{
    QString a="request";
    socket->write(a.toLatin1());
}
