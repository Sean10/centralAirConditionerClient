#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QSqlDatabase>
#include <sqlite3.h>
#include <QDebug>
#include <QString>

class databaseControl
{
public:
    databaseControl();
    bool Connect(const QString &dbname);
    void Init();

private:
    QSqlQuery *query;
};

#endif // DATABASECONTROL_H
