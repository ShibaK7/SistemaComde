#ifndef INICIO_H
#define INICIO_H

#include <QMainWindow>
#include <conectabase.h>
#include <QDialog>
#include <QMessageBox>

//Incluimos las librerias para SQL
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

//Incluimos la ventana del administrador General
#include "admgeneral.h"
#include "admarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class inicio; }
QT_END_NAMESPACE

class inicio : public QMainWindow
{
    Q_OBJECT

public:
    inicio(QWidget *parent = nullptr);
    ~inicio();

private slots:
    void on_btnEntrar_clicked();

private:
    Ui::inicio *ui;
    QString Usuario;
    QString Contrasena;
    bool camposVacios();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //ConectaBase mDbConection;
    QSqlQuery *Query;
};
#endif // INICIO_H
