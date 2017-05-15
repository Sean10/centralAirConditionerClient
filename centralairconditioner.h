#ifndef CENTRALAIRCONDITIONER_H
#define CENTRALAIRCONDITIONER_H

#include <QTime>
#include <QObject>
#include <QDebug>

#define LOWSPEED 0
#define MEDIUMSPEED 1
#define HIGHSPEED 2



class centralAirConditioner : public QObject
{
    Q_OBJECT
public:
    centralAirConditioner();
    ~centralAirConditioner();
    int GetTemperature();
    int GetBlowSpeed();
    double GetCost();
    double GetDegree();
    int ChangeTemperature(int tmp);
    int ChangeBlowSpeed(int tmp);
    void Init();
    QTime time;

public slots:
    void TimeStart();
    void TimeStop();

private:
    int temperature;
    int blowSpeed;
    unsigned long timeCount;
    double degree;
    double cost;
};

//extern centralAirConditioner *airConditioner;
extern centralAirConditioner airConditioner ;


#endif // CENTRALAIRCONDITIONER_H
