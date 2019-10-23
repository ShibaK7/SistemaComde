#include "inicio.h"
#include "ui_inicio.h"
#include "qdebug.h"

inicio::inicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::inicio)
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    //Declaraciones para la IG del inicio
    ui->setupUi(this);
    Query = nullptr;
    ui->tusuario->setPlaceholderText("Ingrese su usuario");
    ui->tclave->setPlaceholderText("Ingrese su contraseña");
}

inicio::~inicio()
{
    delete ui;
}


void inicio::on_btnEntrar_clicked()
{

    if(db.open()){
        Usuario = ui->tusuario->text();
        Contrasena = ui->tclave->text();
        QString usuarioGeneral, claveGeneral;
        QMessageBox::information(this,"Connection", "Database Connection Exitosa");
        Query = new QSqlQuery();
        if(Query->exec("SELECT matricula, contrasegna FROM trabajador WHERE matricula ='"+Usuario+"'")){
            Query->next();
            usuarioGeneral = Query->value(0).toString();
            claveGeneral = Query->value(1).toString();
            Query->finish();
            qDebug() << usuarioGeneral;
            qDebug() << claveGeneral;
        }
    }
    else{
        QMessageBox::information(this,"Not Conected", "Database Connection Rechazada");
    }

/*
    //Establecemos el usuario y la contraseña de las cajas de texto
    Usuario = ui->tusuario->text();
    Contrasena = ui->tclave->text();

    //Inicio de Sesion
    if(ui->rAdmGeneral->isChecked()){
        QString error;
        if(!mDbConection.OpenDatabase(&error)){
            QMessageBox::critical(this, "error",error);
            return;
        }
        else{
            QString usuarioGeneral, claveGeneral;
            Query = new QSqlQuery();//QUERY PARA BUSQUEDA DE ADMINISTRADOR
            if(Query->exec("SELECT matricula, contrasegna FROM [COMDE]...[trabajador] WHERE matricula ='"+Usuario+"'")){
                Query->next();
                usuarioGeneral = Query->value(0).toString();
                claveGeneral = Query->value(1).toString();
                Query->finish();
                if(Usuario == usuarioGeneral && Contrasena == claveGeneral)
                {
                    admGeneral *admG = new admGeneral(Usuario);
                    admG->show();
                }
                else
                    QMessageBox::warning(this,"Error","El usuario y la contraseña no coinciden");

                ui->tusuario->clear();
                ui->tclave->clear();
            }
        }

            //No descomentar esta linea
            //mDbConection.CloseDatabase();
        }
*/
}
