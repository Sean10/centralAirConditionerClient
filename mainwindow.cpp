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

    ui->statusBar->addWidget(ui->labelStatus);
    ui->labelStatus->setText(tr("欢迎使用中央空调！"));


    ui->actionLogout->setStatusTip(tr("注销用户并关闭空调。"));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(SendSignalLogout()));
    //显示statusbar
    //connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(ShowMsgLogout()));

//    connect(ui->spinBoxTemperature, SIGNAL(valueChanged(QString)), this, SLOT(valueChangedSlot(QString)));
//    connect(this, SIGNAL(valueChangedF(float)), &airConditioner, SLOT(ChangeWorkTemperature(float)));
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::OnPushButtonStartClicked);
    //setAttribute (Qt::WA_DeleteOnClose);

    clickMux = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowWidgetMain()
{
    qDebug() << __func__ ;
    ui->widgetMain->show();
    ui->widgetInfo->hide();
}

bool MainWindow::UserRegister()
{
    dialog = new QDialog;
    uiDialog = new Ui::Dialog;
    uiDialog->setupUi(dialog);
    dialog->setWindowTitle("登录");
    dialog->show();
    //设置模态dialog
    dialog->setModal(true);
    int exec = dialog->exec();
    if(dialog->Accepted == exec)
    {
        //qDebug() << "debug1";
        airConditioner.SetUser(uiDialog->lineUser->text());
        //qDebug() << "debug2";
        airConditioner.SetRoomNum(uiDialog->lineRoomNum->text());
        ui->labelUser->setText(airConditioner.GetUser());
        ui->labelRoomNum->setText(airConditioner.GetRoomNum());
        //qDebug() << uiDialog->lineUser->text() << uiDialog->lineRoomNum->text();
        //emit DataLogin("","");
        //qDebug() << uiDialog->lineUser->text() << uiDialog->lineRoomNum->text();
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

void MainWindow::OnPushButtonStartClicked()
{
    if(ui->pushButtonStart->text() == tr("开机"))
    {
        emit DataLogin(uiDialog->lineUser->text(), uiDialog->lineRoomNum->text());
        if(checkConnect == 1)
        {
            ui->pushButtonStart->setText(tr("关机"));
            ui->widgetInfo->show();
        }

        //开启从控机

    }
    else if(ui->pushButtonStart->text() == tr("关机"))
    {
        ui->pushButtonStart->setText(tr("开机"));
        ui->widgetInfo->hide();
        checkConnect = 0;
        emit SignalLogout();
        //关闭从控机
    }

}



void MainWindow::SendSignalLogout()
{
    emit SignalLogout();
    this->close();
    //close事件待处理
    //this->closeEvent(this);
}

void MainWindow::ShowMsgLogout()
{
    ui->labelStatus->setText(tr("注销用户并关闭空调。"));
    //暂时无效，注意处理
}

void MainWindow::Init()
{
//    QDateTime time = QDateTime::currentDateTime();
//    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
//    ui->labelTimeDate->setText(strTime);

    //ui->labelTemperature->setText(QString::number(airConditioner.GetTemperature(), 'f', 2));
    //ui->labelTemperature->
    ui->labelConnect->setText("online");

    ui->labelTemperature->setDecMode();
    ui->labelTemperature->setDigitCount(5);
    ui->labelTemperature->display(QString::number(airConditioner.GetTemperature()));

    ui->spinBoxTemperature->setValue(int(airConditioner.GetWorkTemperature()));
    ui->spinBoxTemperature->setMinimum(airConditioner.GetLowTem());
    ui->spinBoxTemperature->setMaximum(airConditioner.GetHighTem());


    ui->labelDegree->setText(tr("0"));
    ui->labelCost->setText(tr("0"));

    ui->labelUser->setText(airConditioner.GetUser());
    ui->labelRoomNum->setText(airConditioner.GetRoomNum());

    ui->comboBoxBlowSpeed->setCurrentIndex(airConditioner.GetTargetBlowSpeed());
    //ui->comboBoxModel->setCurrentIndex(airConditioner.GetTargetWorkModel());
    ui->labelWorkModel->setText(GetWorkModelString(airConditioner.GetWorkModel()));
    //qDebug() << "show my workModel" << airConditioner.GetTargetWorkModel();
    ui->labelBlowSpeed->setText(GetBlowSpeedString(airConditioner.GetBlowSpeed()));

    ui->labelLowTem->setText(QString::number(airConditioner.GetLowTem(), 'f', 2));
    ui->labelHighTem->setText(QString::number(airConditioner.GetHighTem(), 'f', 2));



}


void MainWindow::Refresh()
{
    //ui->labelTemperature;
//    QDateTime time = QDateTime::currentDateTime();
//    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
//    ui->labelTimeDate->setText(strTime);

    ui->labelUser->setText(airConditioner.GetUser());
    ui->labelRoomNum->setText(airConditioner.GetRoomNum());

    //qDebug() << __func__ << airConditioner.GetWorkTemperature();
    //ui->spinBoxTemperature->setValue(int(airConditioner.GetWorkTemperature()));
    //ui->spinBoxTemperature->setMinimum(airConditioner.GetLowTem());
    //ui->spinBoxTemperature->setMaximum(airConditioner.GetHighTem());
    //qDebug() << __func__ << airConditioner.GetWorkTemperature();

    ui->comboBoxBlowSpeed->setCurrentIndex(airConditioner.GetTargetBlowSpeed());
    ui->labelBlowSpeed->setText(GetBlowSpeedString(airConditioner.GetBlowSpeed()));
    //ui->comboBoxModel->setCurrentIndex(airConditioner.GetTargetWorkModel());
    ui->labelWorkModel->setText(GetWorkModelString(airConditioner.GetWorkModel()));

    ui->labelLowTem->setText(QString::number(airConditioner.GetLowTem(), 'f', 2));
    ui->labelHighTem->setText(QString::number(airConditioner.GetHighTem(), 'f', 2));

    ui->spinBoxTemperature->setValue(airConditioner.GetWorkTemperature());
    //ui->comboBoxModel->setCurrentIndex(airConditioner.GetWorkModel());
    ui->comboBoxBlowSpeed->setCurrentIndex(airConditioner.GetBlowSpeed());
    //ui->labelTemperature->setText(QString::number(airConditioner.GetTemperature()));
    ui->labelTemperature->display(QString::number(airConditioner.GetTemperature()));

    ui->labelDegree->setText(QString::number(airConditioner.GetDegree()));
    ui->labelCost->setText(QString::number(airConditioner.GetCost()));
}

QString MainWindow::GetBlowSpeedString(int tmp)
{
    switch(tmp)
    {
    case 0:
        return "低风";
    case 1:
        return "中风";
    case 2:
        return "高风";
    default:
        qDebug() << __func__ << "error";
        return "null";
    }
}

int MainWindow::GetBlowSpeedNum(const QString &tmp)
{
    if(tmp == "低风")
    {
        return 0;
    }else if(tmp == "中风")
    {
        return 1;
    }else if(tmp == "高风")
    {
        return 2;
    }else
    {
        qDebug() << __func__ << "error";
        return -1;
    }
}

int MainWindow::GetWorkModelNum(const QString &tmp)
{
    if(tmp == "制冷")
        return 0;
    else if(tmp == "制热")
        return 1;
    else
    {
        qDebug() << __func__ << "error";
        return -1;
    }
}

QString MainWindow::GetWorkModelString(const int& tmp)
{
    switch(tmp)
    {
    case 0:
            return "制冷";
    case 1:
            return "制热";
    default:
        qDebug() << __func__ << "error";
        return "null";
    }
}

void MainWindow::on_comboBoxBlowSpeed_currentIndexChanged(const QString &arg1)
{
    airConditioner.SetTargetBlowSpeed(GetBlowSpeedNum(arg1));
    airConditioner.SetBlowSpeed(GetBlowSpeedNum(arg1));
}

void MainWindow::on_spinBoxTemperature_valueChanged(int arg1)
{
    //qDebug() << __func__ << airConditioner.GetTemperature() << airConditioner.GetWorkTemperature();
    airConditioner.ChangeWorkTemperature(float(arg1));
}

void MainWindow::ShowConnect()
{
    if(ui->labelConnect->text() == "offline")
    {
        ui->labelConnect->setText("online");
    }
    else if(ui->labelConnect->text() == "online")
    {
        ui->labelConnect->setText("offline");
    }
}
