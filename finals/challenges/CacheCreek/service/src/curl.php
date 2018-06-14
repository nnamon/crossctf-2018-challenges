<?php
if ($_GET['source']) {
    show_source(__file__);
    die();
}
/*
    Adapted from a cache written by Carlo Alberto Ferraris <cafxx@strayorange.com>
*/

define('CACHE_PREFIX', 'qycache_');
define('CACHE_DIR', sys_get_temp_dir());

function cache($url, $min_expiration, $referer="", $params) {
    $min_expiration = max( intval( $min_expiration ), 1 );
    $cache_key = hash('sha256',$url) or die();
    $cache_file = CACHE_PREFIX . $cache_key;
    $cache_file_fullpath = CACHE_DIR . '/' . $cache_file;
    $cache_file_mtime = @filemtime($cache_file_fullpath);

    if ($cache_file_mtime && $cache_file_mtime >= time() - $min_expiration) {
        // we have a cached version less than $min_expiration seconds old - return it
        return $cache_file_fullpath;
    }

    $url_or_file = $cache_file_mtime ? $cache_file_fullpath : $url;
    
    // try to acquire a lock for the url: if it fails either return the stale cached
    // version (if available), the original url otherwise
    $lockn = $cache_file_fullpath . '.lock';
    $lockp = @fopen($lockn, 'w+') or die();
    @flock($lockp, LOCK_EX|LOCK_NB) or die(); 

    // we have our lock, now fetch the url and save it in a temporary file
    $fn = @tempnam(CACHE_DIR, CACHE_PREFIX) or die();
    $fp = @fopen($fn, 'w+b') or die();

    $c = @curl_init() or die();
    @curl_setopt($c, CURLOPT_URL, $url) or die();
    @curl_setopt($c, CURLOPT_FILE, $fp) or die();
    @curl_setopt($c, CURLOPT_REFERER, $referer) or die();
    @curl_setopt($c, CURLOPT_FOLLOWLOCATION, true) or die();
    @curl_setopt($c, CURLOPT_AUTOREFERER, true) or die();
    @curl_setopt($c, CURLOPT_MAXREDIRS, 5) or die();
    @curl_setopt($c, CURLOPT_TIMEOUT, 5) or die();
    @curl_setopt($c, CURLOPT_POST, true) or die();
    @curl_setopt($c, CURLOPT_POSTFIELDS, http_build_query($params)) or die();
    if ($cache_file_mtime)
        @curl_setopt($c, CURLOPT_TIMEVALUE, $cache_file_mtime);
    @curl_exec($c) or die("Something Went Wrong");
    $cs = intval(@curl_getinfo($c, CURLINFO_HTTP_CODE));
    @curl_close($c);
    
    // we finished fetching the url: if it ended succesfully, delete the old cached
    // version and replace it with the new one
    if ($cs >= 200 && $cs < 300) {
        @unlink($cache_file_fullpath);
        link($fn, $cache_file_fullpath) or die();
    }

    // release the lock, close and remove the temporary files
    fclose($fp);
    fclose($lockp);
    unlink($fn);
    unlink($lockn);
    return $cache_file_fullpath;
}

function url_get_contents($url, $min_expiration=60, $referer="", $params=Array()) {
    return file_get_contents( cache( $url, $min_expiration, $referer, $params));
}

?>