#ifndef CONECTABASE_H
#define CONECTABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
class ConectaBase
{
public:
    ConectaBase(const QString &server, const QString &driver, const QString &user,
                const QString &pass, const QString &databasename, bool truster = true);
    bool OpenDatabase(QString *error = nullptr);
    void CloseDatabase();
private:
    QSqlDatabase mDatabase;
    QString mServer;
    QString mDriver;
    QString mUser;
    QString NombreBase;
    QString Password;
    bool trustedconection;
};

#endif // CONECTABASE_H
