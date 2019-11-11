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
    //ui->tusuario->setPlaceholderText("Ingrese su usuario");
    //ui->tclave->setPlaceholderText("Ingrese su contraseña");
}

inicio::~inicio()
{
    delete ui;
}


void inicio::on_btnEntrar_clicked()
{
    //Establecemos el usuario y la contraseña de las cajas de texto
    Usuario = ui->tusuario->text();
    Contrasena = ui->tclave->text();
    if(camposVacios()){
        qDebug() << " Campos Vacios ";
    }else{
        //Inicio de Sesion Administrador General
        if(ui->rAdmGeneral->isChecked()){
            QString error = "No se logro conectar con la Base de Datos";
            if(!db.open()){
                QMessageBox::critical(this, "Error",error);
                return;
            }
            else{
                QString usuarioGeneral, claveGeneral;
                Query = new QSqlQuery();
                if(Query->exec("SELECT matricula, contrasegna FROM trabajador WHERE matricula ='"+Usuario+"' and "
                               "nivel = 1")){
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

        }

        //Inicio de Sesion para el administrador por Area
        if(ui->rAdmArea->isChecked()){
            QString error = "No se logro conectar con la Base de Datos";
            if(!db.open()){
                QMessageBox::critical(this, "Error",error);
                return;
            }
            else{
                QString usuarioGeneral, claveGeneral;
                Query = new QSqlQuery();
                if(Query->exec("SELECT matricula, contrasegna FROM trabajador WHERE matricula ='"+Usuario+"' and "
                               "nivel = 2")){
                    Query->next();
                    usuarioGeneral = Query->value(0).toString();
                    claveGeneral = Query->value(1).toString();
                    Query->finish();
                    if(Usuario == usuarioGeneral && Contrasena == claveGeneral)
                    {
                        admArea *admA = new admArea(Usuario);
                        admA->show();
                    }
                    else
                        QMessageBox::warning(this,"Error","El usuario y la contraseña no coinciden");

                    ui->tusuario->clear();
                    ui->tclave->clear();
                    ui->rAdmArea->setChecked(false);
                }
            }

        }
    }
}

bool inicio::camposVacios()
{
    if(ui->tclave->text().isEmpty() || ui->tusuario->text().isEmpty()){
        return true;
    }else{
        return false;
    }
}
