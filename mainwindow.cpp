#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "centralairconditioner.h"
//centralAirConditioner *airConditioner;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("中央空调从控机");
    Init();
    timeRefresh->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PushButtonStartClicked()
{
    if(ui->pushButtonStart->text() == tr("开启"))
    {
        ui->pushButtonStart->setText(tr("关闭"));
        //开启从控机
        emit TimeStartSignal();

    }
    else if(ui->pushButtonStart->text() == tr("关闭"))
    {
        ui->pushButtonStart->setText(tr("开启"));
        //关闭从控机
        emit TimeStopSignal();


    }
}

void MainWindow::Init()
{
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);

    ui->spinBoxTemperature->setRange(15,35);
    ui->spinBoxTemperature->setValue(25);
    ui->labelDegree->setText(tr("0.0"));
    ui->labelCost->setText(tr("0.00"));


    //connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(BlowSpeedTransfer(ui->spinBox_2->value())));
    timeRefresh = new QTimer;

    connect(timeRefresh, SIGNAL(timeout()), this, SLOT(Refresh()));
    connect(ui->pushButtonStart,SIGNAL(clicked()), this,SLOT(PushButtonStartClicked()));
}

void MainWindow::Refresh()
{
    ui->labelDegree->setText(QString::number(airConditioner.GetDegree(),'f',1));
    ui->labelCost->setText(QString::number(airConditioner.GetCost(),'f',2));
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);
}
