<?php

    session_start();

    require 'database.php';

    /*if(!empty($_POST['usuario']) && !empty($_POST['password'])) {
        $records = $conn->prepare('SELECT matricula, nombre, contrasegna FROM trabajador WHERE matricula=:matricula');
        $records->bindParam(':matricula', $_POST['usuario']);
        $records->execute();
        $results = $records->fetch(PDO::FETCH_ASSOC);

        $message = '';

        if(count($results) > 0 && password_verify($_POST['password'], $results['contrasegna'])) {
            $message = '';
            $_SESSION['id'] = $results['matricula'];
            header('Location: /php-index');
        } else {
            $message = 'Contrasegna incorrecta';
        }
    } else {
        $message = 'Ingresa tus datos'; 
    }*/
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Login</title>
    <link href="https://fonts.googleapis.com/css?family=Roboto&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/style.css">
</head>
<body>

    <?php require 'partials/header.php'?>

    <h1>Login</h1>

    <?php if(!empty($message)) : ?>
        <p><?= $message?></p>
    <?php endif;?>

    <?php
    if($_POST) {
        $matri = $_POST['usuario'];
        $contra = $_POST['password'];
    } else {
        ?>
        <form action="logica/login.php" method="post">
            <input type="text" id="usuario" name="usuario" placeholder="Introduce tu matrícula">
            <input type="password" id="password" name="password" placeholder="Introduce tu contraseña">
            <input type="submit" id="enviar" value="Enviar">
        </form>
        <?php
    }
    ?>

</body>
</html>