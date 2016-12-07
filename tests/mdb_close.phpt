--TEST--
mdb_close() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb");
echo is_resource($mdb) ? "OK\n" : "Failed\n";
mdb_close($mdb);
echo is_resource($mdb) ? "Failed\n" : "OK\n";

?>
--EXPECT--
OK
OK
