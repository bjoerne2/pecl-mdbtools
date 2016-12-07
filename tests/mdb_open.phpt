--TEST--
mdb_open() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb");
echo is_resource($mdb) ? "OK" : "Failed";

?>
--EXPECT--
OK
