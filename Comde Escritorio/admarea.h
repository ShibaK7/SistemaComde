#ifndef ADMAREA_H
#define ADMAREA_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

//Incluimos las librerias para SQL
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>


namespace Ui {
class admArea;
}

class admArea : public QDialog
{
    Q_OBJECT

public:
    void cargarEmpleados();
    void cargarCursos();
    void cargarGR();
    void cargarComboBoxs();
    explicit admArea(QString,QWidget *parent = nullptr);
    ~admArea();

private slots:
    void on_btnConfirmar_clicked();

    void on_btnActualizar_clicked();

    void on_lEmpleados_itemClicked(QTableWidgetItem *item);

    void on_lCursos_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_aceptarGR_clicked();

    void on_btnPerfil_clicked();

    void on_btnAlta_clicked();

    void on_btnEdicion_clicked();

    void on_btnAltaCursos_clicked();

    void on_btnGestionarRecursos_clicked();

    void cambiaSeleccion();

    void on_btnCerrarSesion_clicked();

    void inforUsuario(QString mat);

    bool buscaMatricula(QString mat);

    void on_btnActualizarEdo_clicked();

    bool buscaProfesorCurso(QString mat);

private:
    Ui::admArea *ui;
};

#endif // ADMAREA_H
