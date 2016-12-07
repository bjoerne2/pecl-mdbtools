--TEST--
mdb_table_fields() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb") or die("Open failed");

$tab = mdb_table_open($mdb, "Tabelle1") or die("Table open failed");

print_r(mdb_table_fields($tab));

?>
--EXPECT--
Array
(
    [0] => Array
        (
            [name] => ID
            [type] => 4
            [size] => 4
            [prec] => 0
            [scale] => 0
            [isfixed] => 1
        )

    [1] => Array
        (
            [name] => f1
            [type] => 10
            [size] => 50
            [prec] => 0
            [scale] => 0
            [isfixed] => 0
        )

    [2] => Array
        (
            [name] => f2
            [type] => 12
            [size] => 0
            [prec] => 0
            [scale] => 0
            [isfixed] => 0
        )

)
