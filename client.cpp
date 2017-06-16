#include "client.h"
#include "centralairconditioner.h"

client::client(QObject *parent):
    QTcpServer (parent)
{
    qDebug() << "client init";
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(RevInitData()));
    //Login("123","1234");
}

void client::Login(QString user, QString roomNum)
{
    qDebug() << __func__ << "is running";
    socket->connectToHost("127.0.0.1", 6666);
    //socket->connectToHost(QHostAddress("192.168.43.104"), 6666);
    qDebug() << socket->errorString();
    if (socket->waitForConnected(100))
    {
        //qDebug() << "error2";
        checkConnect = 1;
        QString a = "clientMsg/"+roomNum+"/"+user;
        socket->write(a.toLatin1());
        //qDebug() << "socket success!";
    }
    else
    {
        checkConnect = 0;
        QMessageBox::warning(NULL,"warning","连接超时/失败");
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
    airConditioner.SetLowTemp(lowTem);
    airConditioner.SetHighTemp(highTem);
    airConditioner.SetWorkModel(workModel);

    //qDebug() << workModel << lowTem << highTem;

    disconnect(socket, SIGNAL(readyRead()), this, SLOT(RevInitData()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(RevData()));
    emit TransMainWindow(workModel, lowTem, highTem);
}

void client::RevData()
{
    QString datas = socket->readAll();
    emit SignalRefresh();
    qDebug() << datas;
    QStringList list = datas.split("/");


    if(QString::compare(QString(list[0]),"cost")==0)
    {
        //emit RefreshCost(QString(list[1]),QString(list[2]));
        //qDebug() << "Get cost" << list[1] << list[2];
        airConditioner.SetDegree(list[1].toFloat());
        airConditioner.SetCost(list[2].toFloat());
        //qDebug() << airConditioner.GetDegree() << airConditioner.GetCost();
    }
    if(QString::compare(QString(list[0]),"request")==0)
    {
        QString a= "answer/"+QString::number(airConditioner.GetTemperature(), 'f', 2)+"/"+QString::number(airConditioner.GetWorkTemperature(), 10)\
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
    QString a="request/"+QString::number(airConditioner.GetTemperature(), 'f', 2)+"/"+QString::number(airConditioner.GetWorkTemperature(), 10);
    qDebug() << "send" << a;
    socket->write(a.toLatin1());
}

void client::Logout()
{
    socket->abort();
    socket->close();
}

void client::SendBlowSpeed()
{
    //不应该从BlowSpeed那里发送，因为需要得到主控机回复的acceptWind才可以切换应该
    QString a = "wind/" + QString::number(airConditioner.GetTargetBlowSpeed(), 10);
    socket->write(a.toLatin1());
}

QTcpSocket *client::GetSocket()
{
    return socket;
}
