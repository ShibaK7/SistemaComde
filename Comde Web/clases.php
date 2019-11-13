<?php

    require 'database.php';
    session_start();

    $matriculaProfesor= $_SESSION['usuario'];

    $records = $conn->prepare("SELECT DISTINCT hor.hora_inicio, hor.hora_final, cua.nombreCurso, cua.idCurso FROM horario AS hor
                                INNER JOIN curso AS cur on hor.idHorario=cur.idHorario
                                INNER JOIN curso_abierto as cua on cua.idCurso=cur.idCurso
                                INNER JOIN asistencia
                                WHERE cur.matriculaProfesor=:matri and hor.hora_inicio <= CURRENT_TIME
                                AND hor.hora_final >= CURRENT_TIME AND asistencia.fecha = '2019-10-23'");
                                                                                        // 2019-10-23
                                                                                        // CURRENT_DATE
    $records->bindParam(':matri', $matriculaProfesor);
    $records->execute();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Cursos abiertos</title>
    <link href="https://fonts.googleapis.com/css?family=Roboto&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/style2.css">
    <link rel="stylesheet" href="assets/css/botones.css">
    <link rel="stylesheet" href="assets/css/boton.css">
</head>
<body>

<?php require 'partials/header.php'?>

<form action="index.php">
    <input id="byebye" class="cerrar" type="submit" value="Cerrar sesión" />
</form>

<table>
    <thead>
        <tr>
            <th>Nombre del curso</th>
            <th>Horario</th>
            <th></th>
        </tr>
    </thead>
    <tbody>
        <?php while($row = $records->fetch()) : ?>
        <tr>
            <td><?php echo $row['nombreCurso']; ?></td>
            <td><?php echo $row['hora_inicio'];?> - <?php echo $row['hora_final']; ?></td>
            <td><?php echo '<span type="button" class="abrir" onClick= "mostrarCurso('.$row['idCurso'].')" >
            <img src="assets/note.png" width="27" height="27"></span>'; ?></td>
        </tr>
        <?php endwhile ?>
    </tbody>
</table>
    
</body>
</html>

<script>

    function mostrarCurso(a) {
        document.cookie = 'name=' + a;
        location.replace("/ProyectoCalidad/lista.php");
    }

</script>
