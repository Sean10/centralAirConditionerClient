#ifndef CENTRALAIRCONDITIONER_H
#define CENTRALAIRCONDITIONER_H

#include <QTime>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QtMath>

#define LOWSPEED 0
#define MEDIUMSPEED 1
#define HIGHSPEED 2



class centralAirConditioner : public QObject
{
    Q_OBJECT
public:
    centralAirConditioner();
    ~centralAirConditioner();
    float GetTemperature();
    float GetWorkTemperature();
    int GetBlowSpeed();
    int GetTargetWorkModel();
    int GetTargetBlowSpeed();
    float GetCost();
    int GetDegree();
    void SetUser(const QString&);
    void SetRoomNum(const QString&);
    void SetWorkModel(const int&);
    void SetLowTemp(const float&);
    void SetHighTemp(const float&);
    void SetTargetWorkModel(const int &);
    void SetTargetBlowSpeed(const int &);
    void SetBlowSpeed(const int&);
    void SetDegree(const int&);
    void SetCost(const float&);
    QString GetUser();
    QString GetRoomNum();
    int GetWorkModel();
    float GetLowTem();
    float GetHighTem();

    int ChangeBlowSpeed(int tmp);
    void Init();
    bool Check();
    void TransTemperature(int, float);
    QTime time;
    QTimer *dataRefresh;

public slots:
    void ChangeTemperature();
    void RevState(int, float, float);
    void RevCost(QString, QString);
    void DataNormalRefresh();
    void SendSignalRequest();
    void ChangeBlowSpeed(); //这个似乎需要传入主控机发来的包吧，但是他的代码里没有。
    void ChangeWorkTemperature(float tmp);
    //void ChangeWorkModel(int);

signals:
    void SignalRequestEnd();
    void SignalRequest();
    void SignalBlowSpeed();
    void SignalInit();


private:
    QString user;
    QString roomNum;
    float temperature;
    float workTemperature;
    int targetBlowSpeed;
    int targetWorkModel;
    int blowSpeed;
    unsigned long timeCount;
    float degree; //能量总数
    float cost;

    int workModel;
    float lowTem;
    float highTem;

    //发送复用信号
    int sendMux;
};

//extern centralAirConditioner *airConditioner;
extern centralAirConditioner airConditioner ;
extern int checkConnect;//初始状态为0，1位连通，2位未连通

#endif // CENTRALAIRCONDITIONER_H
