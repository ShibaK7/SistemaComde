<?php
    $server = 'localhost';
    $username = 'adminscrum';
    $password = 'adminscrum';
    $database = 'basecalidad';

    try {
        $conn = new PDO("mysql:host=$server;dbname=$database;",$username, $password);
    } catch (PDOException $e) {
        die('Connection failed: '.$e->getMessage());
    }
    
?>