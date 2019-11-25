#include <QtTest>
#include <QCoreApplication>

//Incluimos las librerias para SQL
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

//qDebug
#include "qdebug.h"

class Unitarias : public QObject
{
    Q_OBJECT

private slots:
    void testCase1_ConexionBD();
    void testCase2_Login();
    void testCase3_RecuperacionInformacionAdmins();
    void testCase4_RecuperacionCursos();
    void testCase5_HorariosCursos();
private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
};

void Unitarias::testCase1_ConexionBD()
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    qDebug() << "----------Conexión a la Base de Datos----------";
    if(db.open()){
        qDebug() << "PASS: BD OPENED";
    }else{
        qDebug() << "NO PASS: THE DATABASE COULD NOT BE OPENED";
    }
}

void Unitarias::testCase2_Login()
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    qDebug() << "----------Recuperacion de la clave Adm General----------";
    if(db.open()){
        //Recuperación del Administrador General
        QSqlQuery Empleados;
        QString Matricula, Nombre, Puesto, Clave;

        if(Empleados.exec("SELECT T.matricula, T.contrasegna FROM trabajador AS T WHERE nivel = 1")){

        Empleados.next();
            Matricula = Empleados.value(0).toString();
            Clave = Empleados.value(1).toString();
        }
        Empleados.finish();

        //Establecemos los valores que esperamos tener para proceder a realizar la verificacion
        QString cMatricula, cNombre, cPuesto, cClave;
        cMatricula = "100034433";
        cClave = "1728";

        //Realizamos la comparación entre el valor de la matricula esperado y la matricula que se recupera
        QCOMPARE(cMatricula, Matricula);
        QCOMPARE(cClave, Clave);
    }
}

void Unitarias::testCase3_RecuperacionInformacionAdmins()
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    qDebug() << "----------Recuperacion de la información de los Admins (General y Área)----------";
    if(db.open()){
        //Recuperación del Administrador General
        QSqlQuery Empleados;
        QString Matricula, Nombre, Apaterno, Amaterno, Correo, Celular, Edad, Contrasegna, Nivel;

        if(Empleados.exec("SELECT T.matricula, T.nombre, T.apellidoP, T.apellidoM, T.correoE,"
                          "T.celular, T.edad, T.contrasegna, T.nivel FROM trabajador AS T "
                          "WHERE T.nivel = 2 and T.nombre = 'Sandra'")){

        Empleados.next();
            Matricula = Empleados.value(0).toString();
            Nombre = Empleados.value(1).toString();
            Apaterno = Empleados.value(2).toString();
            Amaterno = Empleados.value(3).toString();
            Correo = Empleados.value(4).toString();
            Celular = Empleados.value(5).toString();
            Edad = Empleados.value(6).toString();
            Contrasegna = Empleados.value(7).toString();
            Nivel = Empleados.value(8).toString();
        }


        //Establecemos los valores que esperamos tener para proceder a realizar la verificacion
        QString cMatricula, cNombre, cApaterno, cAmaterno, cCorreo, cCelular, cEdad, cContrasegna, cNivel;
        cMatricula = "100034434";
        cNombre = "Sandra";
        cApaterno = "Rosas";
        cAmaterno = "Ortega";
        cCorreo = "sandra@gmail.com";
        cCelular = "2321259247";
        cEdad = "25";
        cContrasegna = "12345";
        cNivel = "2";

        //Realizamos la verificación entre los valores esperados y los que se recuperan
        QVERIFY(cMatricula == Matricula);
        QVERIFY(cNombre == Nombre);
        QVERIFY(cApaterno == Apaterno);
        QVERIFY(cAmaterno == Amaterno);
        QVERIFY(cCorreo == Correo);
        QVERIFY(cCelular == Celular);
        QVERIFY(cEdad == Edad);
        QVERIFY(cContrasegna == Contrasegna);
        QVERIFY(cNivel == Nivel);
    }
}

void Unitarias::testCase4_RecuperacionCursos()
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    qDebug() << "----------Recuperacion de la información de los Cursos----------";
    if(db.open()){
            //Recuperación del Administrador General
            QSqlQuery Cursos;
            QString IdCurso, Lugar, Instructor;
            if(Cursos.exec("SELECT C.idCurso, l.lugar, T.nombre FROM locacion AS l INNER JOIN curso AS C ON l.idLocacion= C.idLocacion INNER JOIN trabajador AS T ON T.matricula = C.matriculaProfesor WHERE C.idCurso = 1")){
                Cursos.next();
                IdCurso = Cursos.value(0).toString();
                Lugar = Cursos.value(1).toString();
                Instructor = Cursos.value(2).toString();
            }


        //Establecemos los valores que esperamos tener para proceder a realizar la verificacion
        QString cIdCurso, cLugar, cInstructor;
        cIdCurso = "1";
        cLugar = "Dojo Karate COMDE";
        cInstructor = "Laura";

        //Comparamos los resultados con los esperados
        QCOMPARE(cIdCurso,IdCurso);
        QCOMPARE(cLugar,Lugar);
        QCOMPARE(cInstructor,Instructor);
    }
}

void Unitarias::testCase5_HorariosCursos()
{
    //Conexion a la base de datos
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("comde");

    qDebug() << "----------Recuperacion de la información de los Horarios de Cursos----------";
    if(db.open()){
        QSqlQuery dCursos;
        QString matricula, horaini, horafin, numSeccion;
        QString idCurso = "1";

        if(dCursos.exec("SELECT C.matriculaProfesor, H.hora_inicio, H.hora_final, C.idSeccion "
                        "FROM horario as H INNER JOIN curso AS C ON H.idHorario = C.idHorario "
                        "WHERE C.idCurso = '"+idCurso+"'")){

          dCursos.next();
          matricula = dCursos.value(0).toString();
          horaini = dCursos.value(1).toString();
          horafin = dCursos.value(2).toString();
          numSeccion = dCursos.value(3).toString();

          //Valores esperados
          QString cmatricula, choraini, chorafin, cnumSeccion;
          cmatricula = "100034438";
          choraini = "09:00:00";
          chorafin = "11:00:00";
          cnumSeccion = "1";

          //Realizamos la verificación
          QVERIFY(matricula == cmatricula);
          QVERIFY(horaini == choraini);
          QVERIFY(horafin == chorafin);
          QVERIFY(numSeccion == cnumSeccion);
        }
    }
}

QTEST_MAIN(Unitarias)
#include "tst_unitarias.moc"
