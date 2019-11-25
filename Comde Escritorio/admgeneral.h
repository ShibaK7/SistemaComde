#ifndef ADMGENERAL_H
#define ADMGENERAL_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

//Incluimos las librerias para SQL
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

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



namespace Ui {
class admGeneral;
}

class admGeneral : public QDialog
{
    Q_OBJECT

public:
    void cargarEmpleados();
    explicit admGeneral(QString,QWidget *parent = nullptr);
    ~admGeneral();

private slots:
    void on_btnConfirmar_clicked();

    void on_lEmpleados_itemClicked(QTableWidgetItem *item);

    void on_btnActualizar_clicked();

    void on_btnPerfil_clicked(bool checked);

    void on_btnAlta_clicked(bool checked);

    void on_btnEdicion_clicked(bool checked);

    void cambiaSeleccion();

    void on_btnCerrarSesion_clicked(bool checked);

    void inforUsuario(QString mat);

    void on_pushButton_clicked();

    void on_btnAlta_clicked();

    bool buscaMatricula(QString mat);

    void on_btnActualizarEdo_clicked();

private:
    Ui::admGeneral *ui;
    QSqlQuery *Query;
    QString Usuario;

};

#endif // ADMGENERAL_H
