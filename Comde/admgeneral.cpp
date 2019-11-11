#include "admgeneral.h"
#include "ui_admgeneral.h"
#include "qdebug.h"

admGeneral::admGeneral(QString user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admGeneral)
{
    ui->setupUi(this);
    //Mandamos a imprimir el nombre del usuario que ingreso
    qDebug()<< user;

    //Se inicializa en el Perfil
    ui->tabWidget->setCurrentIndex(0);
    ui->btnPerfil->setStyleSheet("background-color: rgb(0,143,189)");
}

admGeneral::~admGeneral()
{
    delete ui;
}

void admGeneral::cargarEmpleados(){
    QSqlQuery Empleados;
    QString Matricula, Nombre, Puesto;
    Empleados.exec("SELECT T.matricula, T.nombre, T.apellidoP, T.apellidoM,T.correoE, T.celular, T.edad, NT.puesto "
                   "FROM trabajador AS T INNER JOIN nivel_trabajador AS NT ON T.nivel = NT.nivelTrabajador "
                   "WHERE nivel = 2");


    int numEmpleados = ui->lEmpleados->rowCount();
    for(int i=0; i<numEmpleados;i++){
        ui->lEmpleados->setRowCount(i);
    }
    ui->lEmpleados->setRowCount(0);

    while(Empleados.next()){
        int c = 0;
        Matricula = Empleados.value(0).toString();
        Nombre = Empleados.value(1).toString()+" "+Empleados.value(2).toString()+" "+Empleados.value(3).toString();
        Puesto = Empleados.value(7).toString();

        ui->lEmpleados->insertRow(ui->lEmpleados->rowCount());
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Matricula));
        c++;
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Nombre));
        c++;
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Puesto));
    }
    ui->lEmpleados->resizeColumnsToContents();
    Empleados.finish();
}

void admGeneral::on_btnConfirmar_clicked()
{
    QString mat,nom,ap,am,ce,cel,edad,clave,clave2,nivel;
    //Recuperando los valores de los campos del formulario
    mat = ui->tMatricula->text();
    nom = ui->tNombre->text();
    ap  = ui->tApaterno->text();
    am  = ui->tAmaterno->text();
    ce  = ui->tCorreo->text();
    cel = ui->tCelular->text();
    edad = ui->sEdad->text();
    clave = ui->tClave->text();
    clave2 = ui->tClaveC->text();


    //Procederemos a verificar que los campos principales no estan vacios
    if(!mat.isEmpty() || !nom.isEmpty() || !ap.isEmpty() || !am.isEmpty()){
        if(clave == clave2){
            //Procederemos a ejecutar el query para el insert
            QMessageBox::StandardButton resp;
            resp=QMessageBox::question(this,tr("Aviso"),tr("¿Estas seguro de crear este usuario?,"
                                                           "\nEsta acción no se puede deshacer:"),
                                  QMessageBox::Ok | QMessageBox::No);
            if(resp==QMessageBox::Ok){
                QSqlQuery query;
                query.exec("INSERT INTO trabajador (matricula,nombre,apellidoP,apellidoM,correoE,"
                           "celular,edad,contrasegna,nivel)"
                           "VALUES ('"+mat+"','"+nom+"','"+ap+"','"+am+"','"+ce+"','"+cel+"','"+edad+"'"
                           ",'"+clave+"','2')"
                           );
                query.finish();
            }

            //Limpiamos las cajas de texto
            ui->tMatricula->clear();
            ui->tNombre->clear();
            ui->tNombre->clear();
            ui->tApaterno->clear();
            ui->tAmaterno->clear();
            ui->tCorreo->clear();
            ui->tCelular->clear();
            ui->sEdad->clear();
            ui->tClave->clear();
            ui->tClaveC->clear();
        }
        else{
            ui->tClaveC->clear();
            QMessageBox::critical(this, "Error","Las contraseñas no coinciden");
        }
    }
    else{
        QMessageBox::critical(this, "Error","Rellene todos los campos");
    }

}

void admGeneral::on_lEmpleados_itemClicked(QTableWidgetItem *item)
{
    QString Matricula, Nombre, Puesto;
    QString nombre, ap, am, mail, cel, edad;
    QSqlQuery dEmpleados;
    QList<QTableWidgetItem *>Empleado;
    Empleado = ui->lEmpleados->selectedItems();

    Matricula = Empleado.value(0)->text();
    Puesto = Empleado.value(2)->text();

    if(dEmpleados.exec("SELECT T.nombre, T.apellidoP, T.apellidoM,T.correoE, T.celular, T.edad "
                       "FROM trabajador AS T INNER JOIN nivel_trabajador AS NT "
                       "ON T.nivel = NT.nivelTrabajador "
                       "WHERE T.nivel = 2 and T.matricula = '"+Matricula+"'")){
        dEmpleados.next();

        nombre = dEmpleados.value(0).toString();
        ap = dEmpleados.value(1).toString();
        am = dEmpleados.value(2).toString();
        mail = dEmpleados.value(3).toString();
        cel = dEmpleados.value(4).toString();
        edad = dEmpleados.value(5).toString();

        ui->cMatricula->setText(Matricula);
        ui->cNombre->setText(nombre);
        ui->cAP->setText(ap);
        ui->cAM->setText(am);
        ui->cCorreo->setText(mail);
        ui->cCelular->setText(cel);
        ui->cEdad->setText(edad);
    }
    dEmpleados.finish();


}

void admGeneral::on_btnActualizar_clicked()
{
    QString nom, ap, am, correo, cel, Matricula;
    Matricula = ui->cMatricula->text();
    nom = ui->cNombre->text();
    ap  = ui->cAP->text();
    am  = ui->cAM->text();
    correo = ui->cCorreo->text();
    cel = ui->cCelular->text();

    QMessageBox::StandardButton resp;
    resp=QMessageBox::question(this,tr("Aviso"),tr("¿Estas seguro de modificar este usuario?,"
                                                   "\nEsta acción no se puede deshacer:"),
                          QMessageBox::Ok | QMessageBox::No);
    if(resp==QMessageBox::Ok){
        QSqlQuery query;
        query.exec("UPDATE trabajador SET nombre = '"+nom+"' , apellidoP = '"+ap+"', apellidoM = '"+am+"'"
                   ", correoE = '"+correo+"', celular = '"+cel+"' "
                   "WHERE matricula = '"+Matricula+"' ");
        query.finish();
    }
    cargarEmpleados();
}

void admGeneral::on_btnPerfil_clicked(bool checked)
{
    ui->tabWidget->setCurrentIndex(0);
    cambiaSeleccion();
    ui->btnPerfil->setStyleSheet("background-color: rgb(0,143,189)");
}

void admGeneral::on_btnAlta_clicked(bool checked)
{
    ui->tabWidget->setCurrentIndex(1);
    cambiaSeleccion();
    ui->btnAlta->setStyleSheet("background-color: rgb(0,143,189)");
}

void admGeneral::on_btnEdicion_clicked(bool checked)
{
    cargarEmpleados();
    ui->tabWidget->setCurrentIndex(2);
    cambiaSeleccion();
    ui->btnEdicion->setStyleSheet("background-color: rgb(0,143,189)");
}

void admGeneral::cambiaSeleccion(){
    ui->btnPerfil->setStyleSheet("pressedbackground-color: none");
    ui->btnAlta->setStyleSheet("background-color: none");
    ui->btnEdicion->setStyleSheet("background-color: none");
    ui->btnPerfil->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnAlta->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnEdicion->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
}

void admGeneral::on_btnCerrarSesion_clicked(bool checked)
{
    this->close();
}
