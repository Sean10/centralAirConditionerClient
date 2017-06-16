#include "databasecontrol.h"

databaseControl::databaseControl()
{
    //qDebug() << QSqlDatabase::drivers();
    if(Connect("airConditioner.db")){
        qDebug() << "Database Create Sucessfully!";
    }
    else{
        qDebug() << "Database Create Failed!";
    }
    Init();
}

void databaseControl::Init()
{
    //query = new QSqlQuery;
}

bool databaseControl::Connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open())
    {
        qDebug() << "Database open error!";
        return false;
    }
    else
    {
        return true;
    }
}
