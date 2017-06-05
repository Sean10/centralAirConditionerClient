#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialoguserregister.h"
#include "centralairconditioner.h"
//centralAirConditioner *airConditioner;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("中央空调从控机");
    if(!UserRegister())
    {
        this->close();
        //this->hide();
        //待修正关闭事件
    }
    Init();
    timeRefresh->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::UserRegister()
{
    dialog = new QDialog;
    Ui::Dialog *uiDialog = new Ui::Dialog;
    uiDialog->setupUi(dialog);
    dialog->setWindowTitle("登录");
    dialog->show();
    //设置模态dialog
    dialog->setModal(true);
    int exec = dialog->exec();
    if(dialog->Accepted == exec)
    {
        airConditioner.SetUser(uiDialog->lineUser->text());
        airConditioner.SetRoomNum(uiDialog->lineRoomNum->text());
        emit DataLogin(uiDialog->lineUser->text(), uiDialog->lineRoomNum->text());
    }
    else if(dialog->Rejected == exec)
    {

        qDebug() << "Canceled." << endl;
        dialog->close();
        this->close();
        setAttribute (Qt::WA_DeleteOnClose);
        //这句话可以关闭窗口

        return 0;
    }
    else
    {
        qDebug() << "login error." << endl;
    }
    return 1;
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

    ui->labelTemperature->setText(QString::number(airConditioner.GetTemperature(), 'f', 2));

    ui->spinBoxTemperature->setMinimum(airConditioner.GetLowTem());
    ui->spinBoxTemperature->setMaximum(airConditioner.GetHighTem());
    ui->spinBoxTemperature->setValue(airConditioner.GetWorkTemperature());

    ui->labelDegree->setText(tr("0.0"));
    ui->labelCost->setText(tr("0.00"));

    ui->labelUser->setText(airConditioner.GetUser());
    ui->labelRoomNum->setText(airConditioner.GetRoomNum());

    ui->comboBoxModel->setCurrentText(QString::number(airConditioner.GetWorkModel(), 10));

    ui->labelLowTem->setText(QString::number(airConditioner.GetLowTem(), 'f', 2));
    ui->labelHighTem->setText(QString::number(airConditioner.GetHighTem(), 'f', 2));

    //connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(BlowSpeedTransfer(ui->spinBox_2->value())));
    timeRefresh = new QTimer;

    connect(timeRefresh, SIGNAL(timeout()), this, SLOT(Refresh()));
    connect(ui->pushButtonStart,SIGNAL(clicked()), this,SLOT(PushButtonStartClicked()));

    setAttribute (Qt::WA_DeleteOnClose);

    clickMux = 0;

}

void MainWindow::Refresh()
{
    //ui->labelTemperature;
    ui->labelDegree->setText(QString::number(airConditioner.GetDegree(), 10));
    ui->labelCost->setText(QString::number(airConditioner.GetCost(),'f',2));
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);
}

