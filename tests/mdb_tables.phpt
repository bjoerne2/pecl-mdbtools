--TEST--
mdb_tables() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb") or die("Failed");

print_r(mdb_tables($mdb));

?>
--EXPECT--
Array
(
    [0] => Tabelle1
)
