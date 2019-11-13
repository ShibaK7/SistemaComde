#include "admgeneral.h"
#include "ui_admgeneral.h"
#include "qdebug.h"

//Para las gráficas
#include <QThread>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

//Reportes
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QBrush>
QT_CHARTS_USE_NAMESPACE

using namespace QtCharts;
//Fin Graficas


admGeneral::admGeneral(QString user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admGeneral)
{
    ui->setupUi(this);
    //Mandamos a imprimir el nombre del usuario que ingreso
    qDebug()<< user;
    inforUsuario(user);
    Usuario = user;

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

void admGeneral::inforUsuario(QString id)
{
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

void admGeneral::on_btnCerrarSesion_clicked(bool checked)
{
    this->close();
}

void admGeneral::on_pushButton_clicked()
{
    QSqlQuery query;

    //QPixmap
    QPixmap imagenReporte(":/new/reporte/imagenes/templateReportes.png");

    //PDF para cada reporte
    QPdfWriter pdf_inscripciones("ReporteInscripciones.pdf");
    QPdfWriter pdf_horarios("ReporteHorarios.pdf");

    //QPainter para cada pdf
    QPainter painter_inscripciones(&pdf_inscripciones);
    QPainter painter_horarios(&pdf_horarios);

    //Draw para cada painter
    painter_inscripciones.drawPixmap(QRect(0,0,9500,13700), imagenReporte);
    painter_horarios.drawPixmap(QRect(0,0,9500,13700),imagenReporte);

    //Estilo de fuente
    QFont estilo("Sans Serif", 20);
    QFont estiloTexto("Sans Serif", 10);

    //Asignacion del estilo de fuente
    painter_inscripciones.setFont(estilo);
    painter_horarios.setFont(estilo);

    //Estilo de lápiz
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidthF(600);

    //Asignacion de lápiz
    painter_inscripciones.setPen(pen);
    painter_horarios.setPen(pen);

    //Constante linea
    int linea = 4000;

    if(ui->radioButton->isChecked()){

        QString hora = QDateTime::currentDateTime().toString();
        painter_inscripciones.setFont(estiloTexto);
        painter_inscripciones.drawText(1000, 3000, Usuario);
        painter_inscripciones.drawText(8000,3000,hora);
        painter_inscripciones.setFont(estilo);
        painter_inscripciones.drawText(3600,3500,"Reporte de Inscripciones");
        painter_inscripciones.setFont(estiloTexto);
        QBarSet *set0 = new QBarSet("Cursos (El nombre del curso se establece en la primer hoja).");

        QStringList categorias;

        int i=1;

        if(query.exec("SELECT ca.nombreCurso, COUNT(a.idCurso) "
                      "FROM alumno as a INNER JOIN curso_abierto as ca on a.idCurso = ca.idCurso "
                      "GROUP BY a.idCurso ORDER BY a.idCurso")){
            while(query.next()){
                QString matricula = query.value(0).toString();
                QString noSecciones = query.value(1).toString();

                QString comple;
                comple.append(QString::number(i));
                comple.append(".- ");
                comple.append(matricula);

                *set0 << query.value(1).toInt();

                categorias << QString::number(i);

                painter_inscripciones.drawText(1000, linea, comple);
                painter_inscripciones.drawText(8000, linea, noSecciones);
                linea+=300;

                i++;
            }
        }

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart * chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Alumnos Inscritos por Curso");
        chart->setAnimationOptions(QChart::NoAnimation);

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categorias);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QPixmap p = chartView->grab();
        p.save("a.png", "PNG");

        if(pdf_inscripciones.QPdfWriter::newPage())
        {
            QPixmap imagen(":/new/reporte/imagenes/templateReportes.png");
            QPdfWriter pdf1_reportes("ReporteInscripciones.pdf");
            painter_inscripciones.drawPixmap(QRect(0,10,9500,13700), imagen);
            painter_inscripciones.drawPixmap(QRect(800,3000,8500,6000),QPixmap(p));
            painter_inscripciones.end();
        }

        QDesktopServices::openUrl(QUrl::fromLocalFile("ReporteInscripciones.pdf"));
    }

    if(ui->radioButton_2->isChecked()){

        QString hora = QDateTime::currentDateTime().toString();
        painter_horarios.setFont(estiloTexto);
        painter_horarios.drawText(1000, 3000, Usuario);
        painter_horarios.drawText(8000,3000,hora);
        painter_horarios.setFont(estilo);
        painter_horarios.drawText(3600,3500,"Reporte de Inscripciones");
        painter_horarios.setFont(estiloTexto);
        QBarSet *set0 = new QBarSet("Horarios (El horario y el id del curso se establecen en la primer hoja).");

        QStringList categorias;

        int i=1;

        if(query.exec("SELECT ca.nombreCurso,h.hora_inicio, h.hora_final, COUNT(c.idHorario) "
                      "FROM alumno as a INNER JOIN curso_abierto as ca on a.idCurso = ca.idCurso "
                      "INNER JOIN curso as c on ca.idCurso = c.idCurso "
                      "INNER JOIN horario as h on c.idHorario = h.idHorario "
                      "GROUP BY c.idCurso, c.idHorario ORDER BY c.idHorario")){
            while(query.next()){
                QString matricula = "El curso "+query.value(0).toString()+ " en un horario de "
                        +query.value(1).toString()+ " a "+query.value(2).toString();
                QString noSecciones = query.value(3).toString();

                QString comple;
                comple.append(QString::number(i));
                comple.append(".- ");
                comple.append(matricula);

                *set0 << query.value(3).toInt();

                categorias << QString::number(i);

                painter_horarios.drawText(1000, linea, comple);
                painter_horarios.drawText(8000, linea, noSecciones);
                linea+=300;

                i++;
            }
        }

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart * chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Alumnos Inscritos por horario");
        chart->setAnimationOptions(QChart::NoAnimation);

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categorias);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QPixmap p = chartView->grab();
        p.save("a.png", "PNG");

        if(pdf_horarios.QPdfWriter::newPage())
        {
            QPixmap imagen(":/new/reporte/templateReportes.png");
            QPdfWriter pdf1_reportes("ReporteHorarios.pdf");
            painter_horarios.drawPixmap(QRect(0,10,9500,13700), imagen);
            painter_horarios.drawPixmap(QRect(800,3000,8500,6000),QPixmap(p));
            painter_horarios.end();
        }

        QDesktopServices::openUrl(QUrl::fromLocalFile("ReporteHorarios.pdf"));
    }
}
