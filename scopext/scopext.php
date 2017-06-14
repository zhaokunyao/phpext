<?php

// ./sapi/cli/php  -ddisplay_errors=On  ext/scopext/scopext.php 

$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('scopext')) {
	dl('scopext.' . PHP_SHLIB_SUFFIX);
}
$module = 'scopext';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
	$str = $function($module);
} else {
	$str = "Module $module is not compiled into PHP";
}
echo "$str\n";
define('EARTH_RADIUS', 6378.137); //地球半径
define('PI', 3.1415926);
class Scope_Utility_Util {
    /**
     * calculateDistance
     *
     * 计算距离
     *
     * @access public
     * @param float
     * @param float
     * @param float
     * @param float
     * @return int
     */
    public static function calculateDistance($lat1, $lng1, $lat2, $lng2) {
        $radLat1 = $lat1 * PI / 180.0;
        $radLat2 = $lat2 * PI / 180.0;
        $a       = $radLat1 - $radLat2;
        $b       = ($lng1 * PI / 180.0) - ($lng2 * PI / 180.0);
        $s       = 2 * asin(sqrt(pow(sin($a / 2), 2) + cos($radLat1) * cos($radLat2) * pow(sin($b / 2), 2)));
        $s       = $s * EARTH_RADIUS;
        return round($s * 1000);
    }
}

// todo 把这些搞到 tests/001.phpt 中
// 不过那里面的语法实在disgusting

$arrLines   = file(dirname(__FILE__).'/online_cases');
$i = 0;
foreach ($arrLines as $strLine) {
    $strLine    = str_replace("'", "", trim($strLine));
    list($a, $b, $c, $d, $e) = explode(',', $strLine);
    $e  = doubleval($e);
    $f  = Scope_Utility_Util::calculateDistance($a,$b,$c,$d) ;
    $f2 = scopextCalculateDistance($a,$b,$c,$d);
    assert($f === $e && $f2 === $e);
    $i ++;
    if ($i % 1000 === 0) {
        print $i . PHP_EOL;
    }
}


// 性能对比
$intLoopCount   = 1E+8;
$a = 34.83319;
$b = 113.548655;
$c = 34.814867;
$d = 114.346802;
$e = doubleval(72966);

$floatTimeStart = microtime(true);
for($i=0; $i<$intLoopCount; $i++) {
    $f = Scope_Utility_Util::calculateDistance($a, $b, $c, $d);
    if ($f !== $e) {
        throw new exception("$i error");
    }
}
$floatTimeEnd   = microtime(true);
printf("%s, time: %s".PHP_EOL,  "Scope_Utility_Util::calculateDistance", $floatTimeEnd-$floatTimeStart);

$floatTimeStart = microtime(true);
for($i=0; $i<$intLoopCount; $i++) {
    $f = scopextCalculateDistance($a, $b, $c, $d);
    if ($f !== $e) {
        throw new exception("$i error");
    }
}
$floatTimeEnd   = microtime(true);
printf("%s, time: %s".PHP_EOL,  "scopextCalculateDistance", $floatTimeEnd-$floatTimeStart);


