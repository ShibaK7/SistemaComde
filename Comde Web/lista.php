<?php

    require 'database.php';
    session_start();

    $CursoId = $_COOKIE['name'];
    //echo $CursoId;

    $records = $conn->prepare('SELECT al.nombreAlumno, al.apellidoP, al.apellidoM, asis.asisID, asis.presente FROM alumno AS al
                              INNER JOIN curso as cur on al.idCurso=cur.idCurso
                              INNER JOIN asistencia as asis on asis.alumnoID=al.idAlumno
                              WHERE al.idCurso=:cursoid');
    $records->bindParam(':cursoid', $CursoId);
    $records->execute();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Lista</title>
    <link href="https://fonts.googleapis.com/css?family=Roboto&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/style2.css">
    <link rel="stylesheet" href="assets/css/botones.css">
</head>
<body>

    <script
        src="https://code.jquery.com/jquery-3.4.1.min.js"
        integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
        crossorigin="anonymous"></script>

    <?php require 'partials/header.php'?>

    <div class="w3-container">
        <form action="index.php">
            <input id="byebye" class="cerrar" type="submit" value="Cerrar sesión" />
        </form>

        <form action="clases.php">
            <input id="byebye" class="cerrar" type="submit" value="Regresar" />
        </form>
    </div>

    

    <table>
        <thead>
            <tr>
                <th>Nombre</th>
                <th>Apellido paterno</th>
                <th>Apellido Materno</th>
                <th>Asistencia</th>
            </tr>
        </thead>
        <tbody>
            <?php while($row = $records->fetch()) : ?>
            <tr>
                <td><?php echo $row['nombreAlumno']; ?></td>
                <td><?php echo $row['apellidoP']; ?></td>
                <td><?php echo $row['apellidoM']; ?></td>
                <td>
                    <label class="container">
                        <input type="checkbox">
                        <?php echo '<span class="checkmark" onClick="mostrarCurso('.$row['asisID'].')" ></span>'; ?>
                    </label>
                </td>
            </tr>
            <?php endwhile ?>
        </tbody>
    </table>
    
</body>
</html>

<script>
    function mostrarCurso(a) {
        //console.log(a);
        $(document).ready(function() {
            $.ajax({
                url: 'asistencia.php',
                type: 'POST',
                data: {asis: a},
                success: function(resp) {
                     console.log(resp);
                }
            })
        });
    }
</script>
