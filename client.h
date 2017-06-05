#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QDebug>

class client : public QTcpServer
{
    Q_OBJECT
public:
    client(QObject *parent = 0);
    //void Login(QString user, QString roomNum);
public slots:
    void RevInitData();
    void RevData();
    void Login(QString user, QString roomNum);
    void SendRequestEnd();
    void SendRequest();

signals:
    void TransMainWindow(int, float, float);
    void RefreshCost(QString, QString);
    void SignalChangeTemperature();
    void SignalChangeBlowSpeed();

private:
    //QTcpSocket *GetSocket();
    QTcpSocket *socket;


};

#endif // CLIENT_H
