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
    qDebug() << __FILE__ << __func__ << "is running.";

    temperature = 25;
    if(workModel == 0)
        workTemperature = 22;
    else if(workModel == 1)
        workTemperature = 28;
    else
        qDebug() << "error workModel Get.";

    blowSpeed = LOWSPEED;
    targetBlowSpeed = blowSpeed;
    //workModel = ;
    targetWorkModel = workModel;
    degree = 0;
    cost = 0;
    timeCount = 0;
    //qDebug() << __func__ << workTemperature;

    dataRefresh = new QTimer;
    dataRefresh->start(1000);
    //
    connect(dataRefresh, SIGNAL(timeout()), this, SLOT(DataNormalRefresh()));

//    QTimer timerCheck;
//    timerCheck.start(1000);
//    connect(&timerCheck, SIGNAL(timeout()), this, SLOT(Check()));
}

void centralAirConditioner::DataNormalRefresh()
{
    qDebug() << "sendMux: " << sendMux;
    if(sendMux==0)
    {

//        if(workModel == 0 && (temperature - workTemperature) > 0 && (temperature - workTemperature) < 1.0) //制冷模式 房间温度高 但没超过1度
//        {
//            //TransTemperature(0, 0.1);
//            //ChangeTemperature();
//            //qDebug() << "trans temperature" << temperature << workTemperature;
//        }
        if(workModel == 0 && (temperature-workTemperature)>=1.0) //制冷模式 房间温度高 超过1度
        {
            //TransTemperature(0, 0.1);
            //ChangeTemperature();
            sendMux = 2;
            emit SignalRequest();
            //qDebug() << "trans temperature" << temperature << workTemperature;
        }
        else if(workModel == 0 && (temperature-workTemperature) < 1.0)//(workTemperature-temperature) > -1.0) //制冷模式 房间温度低
        {

            TransTemperature(1, 0.1);
            qDebug() << "trans temperature 0model" << temperature << workTemperature;
        }
        else if(workModel == 1 &&(workTemperature-temperature) < 1.0)//(temperature-workTemperature)> -1.0) //制热模式 房间温度高
        {
            TransTemperature(0, 0.1);
            //qDebug() << "trans temperature" << temperature << workTemperature;
        }
//        else if(workModel == 1 && (workTemperature-temperature)<1.0 && (workTemperature - temperature > 0)) //制热模式 房间温度低 没超过过1度
//        {
//            //TransTemperature(1,0.1);
//            //ChangeTemperature();

//            //qDebug() << "trans temperature" << temperature << workTemperature;
//        }
        else if(workModel == 1 && (workTemperature-temperature)>1.0) //制热模式 房间温度低 超过1度
        {
             sendMux = 2;
             emit SignalRequest();
            //ChangeTemperature();
            //qDebug() << "trans temperature" << temperature << workTemperature;
        }
   }
}

void centralAirConditioner::TransTemperature(int mode, float delta)
{
    qDebug() << __func__ << temperature << delta;
    if(mode == 0)
    {
        temperature -= delta;
//        if(temperature - workTemperature >= 1.0)
//            sendMux = 2;
    }
    else
    {
        temperature += delta;
//        if(workTemperature - temperature >= 1.0)
//            sendMux = 2;
    }
}


int centralAirConditioner::GetBlowSpeed()
{
    return this->blowSpeed;
}

int centralAirConditioner::GetTargetBlowSpeed()
{
    return this->targetBlowSpeed;
}

int centralAirConditioner::GetTargetWorkModel()
{
    return this->targetWorkModel;
}

float centralAirConditioner::GetTemperature()
{
    return this->temperature;
}

int centralAirConditioner::GetWorkTemperature()
{
    return this->workTemperature;
}

float centralAirConditioner::GetCost()
{
    return this->cost;
}

float centralAirConditioner::GetDegree()
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

void centralAirConditioner::SetWorkModel(const int& tmp)
{
    this->workModel = tmp;
}

void centralAirConditioner::SetBlowSpeed(const int& tmp)
{
    this->blowSpeed = tmp;
}

void centralAirConditioner::SetTargetBlowSpeed(const int &tmp)
{
    this->targetBlowSpeed = tmp;
}

void centralAirConditioner::SetTargetWorkModel(const int &tmp)
{
    this->targetWorkModel = tmp;
}

void centralAirConditioner::SetLowTemp(const float& temp)
{
    this->lowTem = temp;
}

void centralAirConditioner::SetHighTemp(const float &temp)
{
    this->highTem = temp;
}

void centralAirConditioner::SetDegree(const float &temp)
{
    this->degree = temp;
}

void centralAirConditioner::SetCost(const float &temp)
{
    this->cost = temp;
}

void centralAirConditioner::ChangeWorkTemperature(float tmp)
{
    //qDebug() << __func__ << tmp;
    workTemperature = tmp;
    if(fabs(temperature - workTemperature) > 0.01) //当工作温度和房间温度不相等时
    {
            sendMux=1;
            if(temperature < workTemperature && workModel == 1) //满足制热条件
            {
                sendMux=2;
                emit SignalRequest();
                //qDebug()<<"制热";

            }
            else if(temperature > workTemperature && workModel == 0) //满足制冷条件
            {
                sendMux=2;
                emit SignalRequest();
                //qDebug()<<"制冷";
            }
            else
            {
                qDebug() << "sendMux ChangeWorkTemperature" << sendMux;
                sendMux=0;
            }
            //qDebug() << __func__ << "1" << temperature << workTemperature;
    }
    //qDebug() << __func__ << "2"<< temperature << workTemperature;
}

void centralAirConditioner::ChangeTemperature()
{
    float delta = 0;
    switch(blowSpeed)
    {
        case 0:
            delta = 0.15;
            break;
        case 1:
            delta = 0.2;
            break;
        case 2:
            delta = 0.25;
            break;
        default:
            qDebug() << "改变温度的风速错误！";
    }


    if(workModel == 0)
        temperature -= delta;

    if(workModel == 1)
        temperature += delta;
    qDebug() << "sendMux" << sendMux;

    if(sendMux == 2 && Check() == false)
    {
        if(temperatureState == 0)
        {
            timerTmp = new QTimer;
            connect(timerTmp, SIGNAL(timeout()), this, SLOT(SendSignalRequest()));
            timerTmp->start(2000);
            temperatureState = 1;
        }
        //QTimer::singleShot(1000,this,SLOT(SendSignalRequest())); //降降速
    }

}

bool centralAirConditioner::Check()
{
    if((workModel == 0 && temperature- workTemperature <= 0.0) || (workModel == 1 && temperature - workTemperature >= 0.0))
    {
        if(temperatureState == 1)
        {
            timerTmp->stop();
            disconnect(timerTmp, SIGNAL(timeout()), this, SLOT(SendSignalRequest()));
            delete timerTmp;
            temperatureState = 0;
        }
        emit SignalRequestEnd();
        sendMux=0;
        return true;
    }
    return false;
}

void centralAirConditioner::RevState(int workModel, float lowTem, float highTem)
{
    this->workModel = workModel;
    this->lowTem = lowTem;
    this->highTem = highTem;
    Init();
    emit SignalInit();
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
    this->blowSpeed = targetBlowSpeed;
}

