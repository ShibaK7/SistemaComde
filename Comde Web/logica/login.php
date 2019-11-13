<?php
    require '../database.php';
    session_start();

    $matri = $_POST['usuario'];
    $contra = $_POST['password'];

    $_SESSION['usuario'] = $matri;

    $records = $conn->prepare('SELECT COUNT(*) AS contar FROM trabajador WHERE matricula=:matricula AND contrasegna=:contra');
    $records->bindParam(':matricula', $_POST['usuario']);
    $records->bindParam(':contra', $_POST['password']);
    $records->execute();
    $results = $records->fetch(PDO::FETCH_ASSOC);

    if($results['contar']>0) {
        header('Location: ../clases.php');
    } else {
        header("Location: ../index.php");
    }
?>