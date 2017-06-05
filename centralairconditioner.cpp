#include "centralairconditioner.h"

centralAirConditioner::centralAirConditioner()
{
    ;
}

centralAirConditioner::~centralAirConditioner()
{
    delete this;
}

void centralAirConditioner::Init()
{
    if(workModel == 0)
    {
        temperature = 22;
    }
    else if(workModel == 1)
    {
        temperature = 28;
    }
    else
    {
        qDebug() << "workModel is out of 0 - 1.";
    }

    blowSpeed = LOWSPEED;
    degree = 0;
    cost = 0;
    timeCount = 0;

    dataRefresh = new QTimer;
    dataRefresh->start(4000);
    connect(dataRefresh, SIGNAL(timeout()), this, SLOT(DataNormalRefresh()));
}

void centralAirConditioner::DataNormalRefresh()
{
    if(sendMux==0)
    {
        if(workModel == 0 && (temperature-workTemperature)<1.0) //制冷模式 房间温度高 但没超过1度
        {
            TransTemperature(0, 0.1);
        }
        else if(workModel == 0 && (temperature-workTemperature)>1.0) //制冷模式 房间温度高 超过1度
        {
            ChangeWorkTemperature(workTemperature);
        }
        else if(workModel == 0 && (workTemperature-temperature)>0.0) //制冷模式 房间温度低
        {
            TransTemperature(0,0.1);
        }

        else if(workModel == 1 &&(temperature-workTemperature)>0.0) //制热模式 房间温度高
        {
            TransTemperature(1,0.1);
        }
        else if(workModel == 1 && (workTemperature-temperature)<1.0) //制热模式 房间温度低 没超过过1度
        {
            TransTemperature(1,0.1);
        }
        else if(workModel == 1 && (workTemperature-temperature)>1.0) //制热模式 房间温度低 超过1度
        {
            ChangeWorkTemperature(workTemperature);
        }

    }
}

void centralAirConditioner::TransTemperature(int mode, float delta)
{
    if(mode == 0)
    {
        temperature -= delta;
    }
    else
    {
        temperature += delta;
    }
}


int centralAirConditioner::GetBlowSpeed()
{
    return this->blowSpeed;
}

float centralAirConditioner::GetTemperature()
{
    return this->temperature;
}

float centralAirConditioner::GetWorkTemperature()
{
    return this->workTemperature;
}

float centralAirConditioner::GetCost()
{
    return this->cost;
}

int centralAirConditioner::GetDegree()
{
    return this->degree;
}

QString centralAirConditioner::GetUser()
{
    return this->user;
}

QString centralAirConditioner::GetRoomNum()
{
    return this->roomNum;
}

int centralAirConditioner::GetWorkModel()
{
    return this->workModel;
}

float centralAirConditioner::GetLowTem()
{
    return this->lowTem;
}

float centralAirConditioner::GetHighTem()
{
    return this->highTem;
}

void centralAirConditioner::SetUser(const QString &user)
{
    this->user = user;
}

void centralAirConditioner::SetRoomNum(const QString &roomNum)
{
    this->roomNum = roomNum;
}

void centralAirConditioner::ChangeWorkTemperature(float tmp)
{
    workTemperature = tmp;
    if(fabs(temperature - workTemperature) > 0.01) //当工作温度和房间温度不相等时
    {
            sendMux=1;
            if(temperature < workTemperature && workModel == 1) //满足制热条件
            {
                sendMux=2;
                emit SignalRequest();
                qDebug()<<"制热";

            }
            else if(temperature > workTemperature && workModel == 0) //满足制冷条件
            {
                sendMux=2;
                emit SignalRequest();
                qDebug()<<"制冷";
            }
            else
            {
                sendMux=0;
            }

    }
}

void centralAirConditioner::ChangeTemperature()
{
    float delta = 0;
    switch(blowSpeed)
    {
        case 0:
            delta = 0.1;
            break;
        case 1:
            delta = 0.2;
            break;
        case 2:
            delta = 0.3;
            break;
    }


    if(workModel == 0)
        temperature -= delta;

    if(workModel == 1)
        temperature += delta;


    if(sendMux == 2 && Check() == false)
        QTimer::singleShot(10,this,SLOT(sendSignalRequest())); //降降速

}

bool centralAirConditioner::Check()
{
    if((workModel == 0 && temperature <= workTemperature) || (workModel == 1 && temperature >= workTemperature))
    {
        emit SignalRequestEnd();
        sendMux=0;
        return true;
    }
    return false;
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
    int time_diff = time.elapsed()/100;
    switch(blowSpeed)
    {
        case 0:
            degree += time_diff;
            cost += time_diff * 0.01;
            break ;
        case 1:
            degree += time_diff*2;
            cost += time_diff * 0.02;
            break;
        case 2:
            degree += time_diff*3;
            cost += time_diff * 0.03;
            break;
        default:
            qDebug() << "Error: blowspeed is wrong." << endl;
    }

}

void centralAirConditioner::RevState(int workModel, float lowTem, float highTem)
{
    this->workModel = workModel;
    this->lowTem = lowTem;
    this->highTem = highTem;
    Init();
}

void centralAirConditioner::RevCost(QString degree, QString cost)
{
    this->degree = degree.toInt();
    this->cost = cost.toFloat();
}

void centralAirConditioner::SendSignalRequest()
{
    emit SignalRequest();
}

void centralAirConditioner::ChangeBlowSpeed()
{
    ;
}
