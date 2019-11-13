<?php

    require 'database.php';

    $asis = $_POST['asis'];

    if(!empty($asis)) {
        //$records = $conn->prepare('UPDATE asistencia SET presente=1 WHERE asisID=:asistencia');
        $records = $conn->prepare('SELECT presente FROM asistencia WHERE asisID=:asistencia');
        $records->bindParam(':asistencia', $asis);
        $records->execute();
        $results = $records->fetch(PDO::FETCH_ASSOC);

        if($results['presente']==1) {
            $records2 = $conn->prepare('UPDATE asistencia SET presente=0 WHERE asisID=:asistencia');
            $records2->bindParam(':asistencia', $asis);
            $records2->execute();
            echo 'No esta';
        } else {
            $records3 = $conn->prepare('UPDATE asistencia SET presente=1 WHERE asisID=:asistencia');
            $records3->bindParam(':asistencia', $asis);
            $records3->execute();
            echo 'Si esta';
        }
    }

?>