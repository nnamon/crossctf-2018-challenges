<?php
include_once('./conn/db.php');

if ($_GET['source']) {
    show_source(__file__);
    die();
}
if(!session_id()) {
    session_start();
    date_default_timezone_set('Asia/Singapore');
}

if (isset($_GET['update']) && isset($_POST['profile'])) {
    $connObj = new dbConn();
    $connObj->updateProfile($_SESSION['name'], $_POST['profile']);
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0"/>
    <title>cache me outside, how 'bout dah?</title> 
    <!-- CSS  -->
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <link href="css/materialize.css" type="text/css" rel="stylesheet" media="screen,projection"/>
    <link href="css/style.css" type="text/css" rel="stylesheet" media="screen,projection"/>
</head>
<body>
    <nav class="black" role="navigation">
        <div class="nav-wrapper container"><a id="logo-container" href="#" class="brand-logo"></a>
            <ul class="right hide-on-med-and-down">
                <li><a href="index.php">Home</a></li>
                <?php 
                if ($_SESSION['name']) {
                    echo '<li><a href="login.php?logout">'.$_SESSION['name'].'</a></li>';
                } else {
                    echo '<li><a href="login.php">Login</a></li>';
                }
                ?>
            </ul>

            <ul id="nav-mobile" class="side-nav">
                <li><a href="index.php">Home</a></li>
                <?php 
                if (isset($_SESSION['name'])) {
                    echo '<li><a href="login.php?logout">'.$_SESSION['name'].'</a></li>';
                } else {
                    echo '<li><a href="login.php">Login</a></li>';
                }
                ?>
            </ul>
            <a href="#" data-activates="nav-mobile" class="button-collapse"><i class="material-icons">menu</i></a>
        </div>
    </nav>
    <div class="section no-pad-bot" id="index-banner">
        <div class="container">
            <div class="section">
                <!--   Icon Section   -->
                <div class="row ">
                    <div class="col offset-m1 s10 m10 center-align">
                        View source <a href="?source=1">here</a>.<br/>
                        I wrote a new cache mechanism, it is pretty awesome, try it <a href="cache.php">here</a>.
                    </div>
                </div>

                <?php
                if (!$_SESSION['name']) {
                    echo '
                    <div class="row">
                    <div class="col offset-m2 s8 m8">
                    <div class="icon-block">
                    <p>Login to continue.</p>
                    </div>
                    </div>
                    </div>';
                } else {
                    $connObj = new dbConn();
                    $profile = htmlentities($connObj->getProfile($_SESSION['name'])['profile']);
                    echo '
                    <div class="row">
                    <div class="col offset-m2 s8 m8">
                    <div class="icon-block">
                    <h5 class="center">Update your profile</h5>
                    <form id="register" method="post" action="?update">
                    <p class="heavy">
                    <center>
                    <div class="input-field col s6">
                    <input id="profile" name="profile" type="text" class="validate" required>
                    <label for="profile">Profile</label>
                    </div>
                    <div class="col s2">
                    <button style="margin-top:30px;" class="btn waves-effect waves-light brown" type="submit" name="action">Update <i class="material-icons right">send</i>
                    </button>
                    </div>
                    </center>
                    </p>
                    </form>
                    </div>
                    </div>
                    </div>
                    <div class="row">
                    <div class="col offset-m2 s8 m8">
                    <div class="icon-block">
                    <h5 class="center">View your profile</h5>
                    <p class="heavy">
                    <center>
                    <div class="input-field col s8">
                    '.$_SESSION['name']."'s Profile: ".$profile.'
                    </div>
                    </center>
                    </p>
                    </div>
                    </div>
                    </div>
                    ';
                }
                ?>
            </div>
        </div>
    </div>
    <footer class="page-footer grey">
        <div class="container">
            <div class="row">
                <div class="col l6 s12">
                    <h5 class="white-text">What is CrossCTF?</h5>
                    <p class="grey-text text-lighten-4">CrossCTF is a cyber security competition organized by NTU with collaboration with NUS Greyhats and SMU Whitehats. This also provides a platform for participants to hack safely in Singapore. The other reason is to promote Cyber Security Capture-The-Flag Compeitions in Singapore.</p>
                </div>
            </div>
        </div>
        <div class="footer-copyright">
            <div class="container">
                Made by <a class="white-text text-lighten-3" href="http://materializecss.com">Materialize</a>
            </div>
        </div>
    </footer>


    <!--  Scripts-->
    <script src="https://code.jquery.com/jquery-2.1.1.min.js"></script>
    <script src="js/materialize.js"></script>
    <script src="js/init.js"></script>

</body>
</html>
