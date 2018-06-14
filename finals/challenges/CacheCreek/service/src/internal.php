<?php
if ($_GET['source']) {
    show_source(__file__);
    die();
}

$whitelist = array(
                   '127.0.0.1',
                   '::1'
                   );

if(!in_array($_SERVER['REMOTE_ADDR'], $whitelist)){
    die("die hax0r!!11");
}

include_once('./conn/db.php');
include_once('./curl.php');

// We haz checks method and referer for security!11
if ($_SERVER['REQUEST_METHOD'] == "POST" && strpos($_SERVER['HTTP_REFERER'], 'index.php') !== False ) {
    if ($_POST['debug'] === "True") {
        // Maybe delete the tmp directory
        echo 'rm -f '. CACHE_DIR . '/'.CACHE_PREFIX.'*';
    } else if (isset($_POST['view'])) {
        $connObj = new dbConn();
        $profile = $connObj->getProfile($_POST['view'])['profile'];
        echo $profile;
    }
} else {
    die("die hax0r!!11");
}
?>