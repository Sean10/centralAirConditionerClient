#include "centralairconditioner.h"

centralAirConditioner::centralAirConditioner()
{
    Init();

}

centralAirConditioner::~centralAirConditioner()
{
    delete this;
}

void centralAirConditioner::Init()
{
    temperature = 25;
    blowSpeed = LOWSPEED;
    cost = 0;
    timeCount = 0;
}

int centralAirConditioner::GetBlowSpeed()
{
    return this->blowSpeed;
}

int centralAirConditioner::GetTemperature()
{
    return this->temperature;
}

double centralAirConditioner::GetCost()
{
    return this->cost;
}

int centralAirConditioner::ChangeTemperature(int tmp)
{
    this->temperature = tmp;
    return 0;
}

int centralAirConditioner::ChangeBlowSpeed(int tmp)
{
    this->blowSpeed = tmp;
    return 0;
}

void centralAirConditioner::TimeStart()
{
    time.start();
}

void centralAirConditioner::TimeStop()
{
    int time_diff = time.elapsed();
    switch(blowSpeed)
    {
        case 0:
            cost += time_diff * 0.01;
            break ;
        case 1:
            cost += time_diff * 0.02;
            break;
        case 2:
            cost += time_diff * 0.03;
            break;
        default:
            qDebug() << "Error: blowspeed is wrong." << endl;
    }

}
