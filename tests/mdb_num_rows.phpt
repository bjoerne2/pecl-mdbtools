--TEST--
mdb_num_rows() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb") or die("Open failed");

$tab = mdb_table_open($mdb, "Tabelle1") or die("Table open failed");

echo mdb_num_rows($tab);

?>
--EXPECT--
8
