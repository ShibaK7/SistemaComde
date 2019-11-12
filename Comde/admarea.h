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

private:
    Ui::admArea *ui;
};

#endif // ADMAREA_H
