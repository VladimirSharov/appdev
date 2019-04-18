<?php
$log_file = 'testcurl.txt';
$values = $_POST[ 'db' ];

date_default_timezone_set( "UTC" );
$str = gmdate(" M d Y H:i:s", time() ).' '.$values."\n";

//open file
if(file_exists($log_file))
{
	$fp = fopen($log_file,a);//opened as append mode
	fwrite($fp, $str);
	fclose($fp);
}
else //if not exist, open new
{
	$fp = fopen($log_file,w);
	fwrite($fp, $str);
	fclose($fp);
}
?>