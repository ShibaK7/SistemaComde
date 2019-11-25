#include "admarea.h"
#include "ui_admarea.h"
#include "qdebug.h"

admArea::admArea(QString user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admArea)
{
    ui->setupUi(this);
    //Mandamos a imprimir el nombre del usuario que ingreso
    qDebug()<< user;
    inforUsuario(user);

    //Se inicializa en el Perfil
    ui->tabWidget->setCurrentIndex(0);
    ui->btnPerfil->setStyleSheet("background-color: rgb(0,143,189)");
}

admArea::~admArea()
{
    delete ui;
}

void admArea::cargarCursos(){
   QSqlQuery Cursos;
   QString IdCurso, Lugar, Instructor;
   Cursos.exec("SELECT C.idCurso, l.lugar, T.nombre, T.apellidoP, T.apellidoM "
               "FROM locacion AS l INNER JOIN curso AS C ON l.idLocacion = C.idLocacion "
               "INNER JOIN trabajador AS T ON T.matricula = C.matriculaProfesor");
   int numCursos = ui->lCursos->rowCount();
   for(int i=0; i<numCursos; i++){
       ui->lCursos->setRowCount(i);
   }
   ui->lCursos->setRowCount(0);

   while(Cursos.next()){
       int c = 0;
       IdCurso = Cursos.value(0).toString();
       Instructor = Cursos.value(2).toString()+" "+Cursos.value(3).toString()+" "+Cursos.value(4).toString();
       Lugar = Cursos.value(1).toString();

       ui->lCursos->insertRow(ui->lCursos->rowCount());
       ui->lCursos->setItem(ui->lCursos->rowCount() -1, c, new QTableWidgetItem(IdCurso));
       c++;
       ui->lCursos->setItem(ui->lCursos->rowCount() -1, c, new QTableWidgetItem(Lugar));
       c++;
       ui->lCursos->setItem(ui->lCursos->rowCount() -1, c, new QTableWidgetItem(Instructor));
   }
   ui->lCursos->resizeColumnsToContents();
   Cursos.finish();
}

void admArea::cargarEmpleados(){
    QSqlQuery Empleados;
    QString Matricula, Nombre, Puesto, EstadoP;
    Empleados.exec("SELECT T.matricula, T.nombre, T.apellidoP, T.apellidoM,T.correoE, T.celular, T.edad, NT.puesto, E.estado FROM trabajador AS T "
                   "INNER JOIN nivel_trabajador AS NT ON T.nivel = NT.nivelTrabajador "
                   "INNER JOIN estado as E ON T.estadoTrabajador=E.claveEstado "
                   "WHERE nivel = 3 ORDER BY E.estado");

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
        EstadoP = Empleados.value(8).toString();

        ui->lEmpleados->insertRow(ui->lEmpleados->rowCount());
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Matricula));
        c++;
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Nombre));
        c++;
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(Puesto));
        c++;
        ui->lEmpleados->setItem(ui->lEmpleados->rowCount() -1, c, new QTableWidgetItem(EstadoP));
    }
    ui->lEmpleados->resizeColumnsToContents();
    Empleados.finish();

}

bool admArea::buscaMatricula(QString mat)
{
    QSqlQuery queryBuscaMat;
    queryBuscaMat.prepare("SELECT matricula FROM trabajador WHERE matricula='"+mat+"'");
    queryBuscaMat.exec();
    queryBuscaMat.next();

    QString matBusca = queryBuscaMat.value(0).toString();

    if(matBusca.isEmpty()){
        return false;
    }else{
        return true;
    }
}

void admArea::on_btnConfirmar_clicked()
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
            if(!buscaMatricula(mat)){
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
                               ",'"+clave+"','3')"
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
            }else{
                ui->tMatricula->clear();
                QMessageBox::critical(this, "Error","Esta matricula ya se encuentra registrada");
            }
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

void admArea::on_btnActualizar_clicked()
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

void admArea::on_lCursos_itemClicked(QTableWidgetItem *item)
{
    QSqlQuery dCursos;
    QList<QTableWidgetItem *>Curso;
    Curso = ui->lCursos->selectedItems();
    QString idCurso = Curso.value(0)->text();
    QString locacion = Curso.value(1)->text();
    QString instructor = Curso.value(2)->text();
    QString matricula, horaini, horafin, numSeccion;

    if(dCursos.exec("SELECT C.matriculaProfesor, H.hora_inicio, H.hora_final, C.idSeccion "
                    "FROM horario as H INNER JOIN curso AS C ON H.idHorario = C.idHorario "
                    "WHERE C.idCurso = '"+idCurso+"'")){
      dCursos.next();
      matricula = dCursos.value(0).toString();
      horaini = dCursos.value(1).toString();
      horafin = dCursos.value(2).toString();
      numSeccion = dCursos.value(3).toString();

      ui->lidCurso->setText(idCurso);
      ui->lmProfesor->setText(matricula);
      ui->lnomProfesor->setText(instructor);
      ui->lHorario->setText(horaini);
      ui->lHorarioF->setText(horafin);
      ui->lSeccion->setText(numSeccion);
    }


}

void admArea::on_lEmpleados_itemClicked(QTableWidgetItem *item)
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
                       "WHERE T.nivel = 3 and T.matricula = '"+Matricula+"'")){
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

void admArea::on_pushButton_clicked()
{
    QString idCurso, nombreCurso, area;

    idCurso = ui->cIdCurso->text();
    int idArea;
    area = ui->cbArea->currentText();
    if(area == "Deportes de Combate"){
        idArea = 1;
    }else{
        if(area == "Escuela de Gimnasia"){
            idArea = 2;
        }else{
            idArea = 3;
        }
    }
    nombreCurso = ui->cNombreCurso->text();
    QString areaId = QString::number(idArea);


    if(!nombreCurso.isEmpty() || !idCurso.isEmpty()){
        QMessageBox::StandardButton resp;
        resp=QMessageBox::question(this,tr("Aviso"),tr("¿Estas seguro de crear este Curso?,"
                                                       "\nEsta acción no se puede deshacer:"),
                              QMessageBox::Ok | QMessageBox::No);
        if(resp==QMessageBox::Ok){
            QSqlQuery AddCurso;
            AddCurso.exec("INSERT INTO curso_abierto (idCurso, idArea, nombreCurso) "
                          "values ('"+idCurso+"','"+areaId+"','"+nombreCurso+"')");
            AddCurso.finish();
        }

        ui->cIdCurso->clear();
        ui->cNombre->clear();
    }else{
        QMessageBox::critical(this, "Error","Rellene todos los campos");
    }


}

void admArea::cargarGR(){
    QSqlQuery Cursos;
    QString IdCurso, Lugar, Instructor;
    Cursos.exec("SELECT C.idCurso, T.nombre, T.apellidoP, T.apellidoM "
                "FROM curso AS C INNER JOIN trabajador AS T "
                "ON T.matricula = C.matriculaProfesor");
    int numCursos = ui->lCursos->rowCount();
    for(int i=0; i<numCursos; i++){
        ui->cursosP->setRowCount(i);
    }
    ui->cursosP->setRowCount(0);

    while(Cursos.next()){
        int c = 0;
        IdCurso = Cursos.value(0).toString();
        Instructor = Cursos.value(1).toString()+" "+Cursos.value(2).toString()+" "+Cursos.value(3).toString();

        ui->cursosP->insertRow(ui->cursosP->rowCount());
        ui->cursosP->setItem(ui->cursosP->rowCount() -1, c, new QTableWidgetItem(IdCurso));
        c++;
        ui->cursosP->setItem(ui->cursosP->rowCount() -1, c, new QTableWidgetItem(Instructor));
    }
    ui->cursosP->resizeColumnsToContents();
    Cursos.finish();
}

void admArea::cargarComboBoxs(){

    QSqlQuery locacion, horario, seccion, profesor;
    QString lugar, horaInicio, horaFinal, numSeccion, nomProfesor;

    ui->cbArea->clear();
    ui->cbSeccion->clear();
    ui->cbHorarios->clear();
    ui->cbLocaciones->clear();
    ui->cbMatriculas->clear();

    //Locacion
    locacion.exec("SELECT lugar FROM locacion");

    while(locacion.next()){
        lugar = locacion.value(0).toString();
        ui->cbLocaciones->addItem(lugar);
    }
    locacion.finish();

    //Horario
    horario.exec("SELECT hora_inicio, hora_final FROM horario");

    while(horario.next()){
        horaInicio = horario.value(0).toString();
        horaFinal = horario.value(1).toString();
        ui->cbHorarios->addItem(horaInicio+" - "+horaFinal);
    }
    horario.finish();

    //Seccion
    seccion.exec("SELECT idSeccion FROM seccion");

    while(seccion.next()){
        numSeccion = seccion.value(0).toString();
        ui->cbSeccion->addItem(numSeccion);
    }
    seccion.finish();

    //Profesores
    profesor.exec("SELECT t.matricula, t.nombre, t.apellidoP, t.apellidoM "
                 "FROM curso as c RIGHT JOIN trabajador as t "
                 "ON c.matriculaProfesor = t.matricula "
                 "WHERE T.nivel = 3 AND c.matriculaProfesor IS NULL");

    while(profesor.next()){
        nomProfesor = profesor.value(1).toString()+" "+profesor.value(2).toString()+" "+profesor.value(3).toString();
        ui->cbMatriculas->addItem(nomProfesor);
    }
    profesor.finish();


}

void admArea::on_aceptarGR_clicked()
{
    QSqlQuery query, profesor, matricula, horario, horario2, locacion, locacion2;
    QString clave, nomProfesor, amProfesor, apProfesor, nomCompleto, mat, seccion, horaInicio, horaFinal, horarios;
    QString idHorario, idLocacion, lugar;
    clave = ui->ctIdCurso->text();

    if(!clave.isEmpty()){
        QMessageBox::StandardButton resp;
        resp=QMessageBox::question(this,tr("Aviso"),tr("¿Estas seguro de realizar esta asignación?,"
                                                       "\nEsta acción no se puede deshacer:"),
                              QMessageBox::Ok | QMessageBox::No);

        if(resp==QMessageBox::Ok){
            //Obtenemos la matricula del profesor
            profesor.exec("SELECT t.matricula, t.nombre, t.apellidoP, t.apellidoM "
                         "FROM curso as c RIGHT JOIN trabajador as t "
                         "ON c.matriculaProfesor = t.matricula "
                         "WHERE T.nivel = 3 AND c.matriculaProfesor IS NULL");

            while(profesor.next()){
                nomProfesor = profesor.value(1).toString();
                apProfesor = profesor.value(2).toString();
                amProfesor = profesor.value(3).toString();
                nomCompleto = profesor.value(1).toString()+" "+profesor.value(2).toString()+" "+profesor.value(3).toString();
                if(nomCompleto == ui->cbMatriculas->currentText()){
                    matricula.exec("SELECT t.matricula FROM curso as c RIGHT JOIN trabajador as t "
                                   "ON c.matriculaProfesor = t.matricula WHERE t.nivel = 3 "
                                   "AND c.matriculaProfesor IS NULL AND t.nombre='"+nomProfesor+"' "
                                   "AND t.apellidoP='"+apProfesor+"' "
                                   "AND t.apellidoM='"+amProfesor+"'");

                    while(matricula.next()){
                        mat = matricula.value(0).toString();
                    }
                    matricula.finish();
                }
            }
            profesor.finish();

            //Obtenemos el id de la seccion
            seccion = ui->cbSeccion->currentText();

            //Obtenemos el id del Horario
            horario.exec("SELECT hora_inicio, hora_final FROM horario");

            while(horario.next()){
                horaInicio = horario.value(0).toString();
                horaFinal = horario.value(1).toString();
                horarios = horaInicio+" - "+horaFinal;

                if(horarios == ui->cbHorarios->currentText()){
                    horario2.exec("SELECT idHorario FROM horario WHERE hora_inicio = '"+horaInicio+"' "
                                  "AND hora_final = '"+horaFinal+"'");

                    while(horario2.next()){
                        idHorario = horario2.value(0).toString();
                        qDebug() << idHorario;
                    }
                }
            }
            horario.finish();

            //Obtenemos el id de la locacion
            locacion.exec("SELECT lugar FROM locacion");

            while(locacion.next()){
                lugar = locacion.value(0).toString();
                if(lugar == ui->cbLocaciones->currentText()){
                    locacion2.exec("SELECT idLocacion FROM locacion WHERE lugar='"+lugar+"'");

                    while(locacion2.next()){
                        idLocacion = locacion2.value(0).toString();
                    }
                    locacion2.finish();
                }
            }
            locacion.finish();

            //Procedemos a realizar el alta del curso
            query.exec("INSERT INTO curso (idCurso, matriculaProfesor, idHorario, idLocacion, idSeccion)"
                       "VALUES ('"+clave+"','"+mat+"','"+idHorario+"','"+idLocacion+"','"+seccion+"')");
            query.finish();
        }
    }else{
        QMessageBox::critical(this, "Error","Rellene todos los campos");
    }

}

void admArea::on_btnPerfil_clicked()
{
    cambiaSeleccion();
    ui->tabWidget->setCurrentIndex(0);
    ui->btnPerfil->setStyleSheet("background-color: rgb(0,143,189)");
}

void admArea::on_btnAlta_clicked()
{
    cambiaSeleccion();
    cargarEmpleados();
    ui->tabWidget->setCurrentIndex(1);
    ui->btnAlta->setStyleSheet("background-color: rgb(0,143,189)");
}

void admArea::on_btnEdicion_clicked()
{
    cambiaSeleccion();
    ui->tabWidget->setCurrentIndex(2);
    ui->btnEdicion->setStyleSheet("background-color: rgb(0,143,189)");
}

void admArea::on_btnAltaCursos_clicked()
{
    cambiaSeleccion();
    cargarCursos();
    ui->tabWidget->setCurrentIndex(3);
    ui->btnAltaCursos->setStyleSheet("background-color: rgb(0,143,189)");
}

void admArea::on_btnGestionarRecursos_clicked()
{
    cambiaSeleccion();
    cargarGR();
    cargarComboBoxs();
    ui->tabWidget->setCurrentIndex(4);
    ui->btnGestionarRecursos->setStyleSheet("background-color: rgb(0,143,189)");
}

void admArea::cambiaSeleccion(){
    ui->btnPerfil->setStyleSheet("pressedbackground-color: none");
    ui->btnAlta->setStyleSheet("background-color: none");
    ui->btnEdicion->setStyleSheet("background-color: none");
    ui->btnAltaCursos->setStyleSheet("background-color: none");
    ui->btnGestionarRecursos->setStyleSheet("background-color: none");
    ui->btnPerfil->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnAlta->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnEdicion->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnAltaCursos->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
    ui->btnGestionarRecursos->setStyleSheet("QButton:hover{background-color: rgb(255, 255, 255,80);}");
}

void admArea::inforUsuario(QString id){
    QSqlQuery datosUsuario;
    datosUsuario.prepare("SELECT * FROM trabajador WHERE matricula='"+id+"'");
    datosUsuario.exec();
    datosUsuario.next();
    ui->label_Matricula->setText(datosUsuario.value(0).toString());
    ui->label_Nombre->setText(datosUsuario.value(1).toString());
    ui->label_AP->setText(datosUsuario.value(2).toString());
    ui->label_AM->setText(datosUsuario.value(3).toString());
    ui->label_Correo->setText(datosUsuario.value(4).toString());
    ui->label_Celular->setText(datosUsuario.value(5).toString());
    ui->label_Edad->setText(datosUsuario.value(6).toString());
}

void admArea::on_btnCerrarSesion_clicked()
{
    this->close();
}

bool admArea::buscaProfesorCurso(QString mat)
{
    QSqlQuery queryProfeCurso;
    queryProfeCurso.prepare("SELECT matriculaProfesor FROM curso WHERE matriculaProfesor='"+mat+"'");
    queryProfeCurso.exec();
    queryProfeCurso.next();

    QString buscaProfesor = queryProfeCurso.value(0).toString();

    if(buscaProfesor.isEmpty()){
        return false;
    }else{
        return true;
    }
}

void admArea::on_btnActualizarEdo_clicked()
{
    int Edo = ui->comboEdos->currentIndex()+1;

    qDebug() << ui->cMatricula->text().isEmpty();


    if(ui->cMatricula->text().isEmpty()){
        QMessageBox::warning(this, "Aviso","Selecciona primero a algún trabajador");
    }else{
        if(!buscaProfesorCurso(ui->cMatricula->text())){
            QMessageBox::StandardButton resp;
            resp=QMessageBox::question(this,tr("Aviso"),tr("¿Estas seguro de actualizar el estado?,"
                                                           "\nEsta acción no se puede deshacer:"),
                                  QMessageBox::Ok | QMessageBox::No);
            if(resp==QMessageBox::Ok){
                QSqlQuery queryActualizaEdo;
                queryActualizaEdo.prepare("UPDATE trabajador SET estadoTrabajador="+QString::number(Edo)+" WHERE matricula='"+ui->cMatricula->text()+"'");
                queryActualizaEdo.exec();
                QMessageBox::information(this, "Aviso", "El estado se ha actualizado");
                cargarEmpleados();
            }
        }else{
            QMessageBox::warning(this,"Aviso", "No se puede cambiar el estado. \n Debido a que el profesor tiene asignado algún curso.");
        }
    }
}
