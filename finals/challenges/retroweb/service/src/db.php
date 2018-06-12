<?php

function dbconn() {
    $dbhost = 'localhost';
    $dbuser = 'crossctf';
    $dbpass = '9A&*h^F68l9QgzQyc6C4MajY3SHf332I1ENYcVjb';
    $dbname = 'crossctf';
    $conn = new mysqli($dbhost, $dbuser, $dbpass, $dbname) or die("Wrong info given");
    if ($conn->connect_error) {
        exit();
    }

    $sql = "SET CHARACTER SET 'gbk';";
    $conn->query($sql);

    return $conn;
}

?>