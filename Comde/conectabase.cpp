#include "conectabase.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>

ConectaBase::ConectaBase(const QString &server, const QString &driver, const QString &user,
                         const QString &pass, const QString &databasename, bool truster)
{
     mDatabase = QSqlDatabase::addDatabase("QODBC");
     mServer = server;
     mDriver = driver;
     mUser = user;
     NombreBase = databasename;
     Password = pass;
     trustedconection = truster;
}

bool ConectaBase::OpenDatabase(QString *error)
{
    mDatabase.setDatabaseName(QString("DRIVER={%1};SERVER=%2;DATABASE=%3;UID=%4;PWD=%5;Trusted_Connection=%6;")
             .arg(mDriver).arg(mServer).arg(NombreBase).arg(mUser).arg(Password)
             .arg(trustedconection ? "Yes" : "No"));
    if(!mDatabase.open()){
        if(error != nullptr){
            *error = mDatabase.lastError().text();
        }
        return false;
    }
    return true;
}

void ConectaBase::CloseDatabase()
{
    mDatabase.close();
}
