<?php
    if ($_GET['source']) {
        show_source(__file__);
        die();
    }
    if(!session_id()) {
        session_start();
        date_default_timezone_set('Asia/Singapore');
    }

    include_once("./curl.php");
    if (isset($_GET['report']) && $_GET['report'] === "debug") {
        $debug = url_get_contents("http://127.0.0.1/internal.php?debug". session_id(), 60, "index.php",['debug'=>'True']);
        echo "debug command: ".htmlentities($debug)."<br/>";
        system($debug);
        echo 'debugged!';
        die();
    }

    
    $time1 = microtime(true);

    echo "Caching Admin's Profile:<br />";
    echo htmlentities(url_get_contents("http://127.0.0.1/internal.php?". session_id(), 60, urldecode($_SERVER['HTTP_REFERER']),['view'=>'admin']));
    echo '<br /><br />';
    $time2 = microtime(true);
    $time = ($time2 - $time1)*1000;
    echo 'This script took ' . $time . 'ms to execute'; 
    echo '<br /><br />';
    echo 'Is the script not working? Report it <a href="?report=debug">here</a>'
?>