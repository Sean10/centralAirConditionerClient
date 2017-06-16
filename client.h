#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>

class client : public QTcpServer
{
    Q_OBJECT
public:
    client(QObject *parent = 0);
    QTcpSocket *GetSocket();

    //void Login(QString user, QString roomNum);
public slots:
    void RevInitData();
    void RevData();
    void Login(QString user, QString roomNum);
    void SendRequestEnd();
    void SendRequest();
    void SendBlowSpeed();
    void Logout();

signals:
    void TransMainWindow(int, float, float);
    void RefreshCost(QString, QString);
    void SignalChangeTemperature();
    void SignalChangeBlowSpeed();
    void SignalRefresh();

private:
    //QTcpSocket *GetSocket();
    QTcpSocket *socket;


};

#endif // CLIENT_H
