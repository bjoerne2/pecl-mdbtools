--TEST--
mdb_table_indexes() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb") or die("Open failed");

$tab = mdb_table_open($mdb, "Tabelle1") or die("Table open failed");

print_r(mdb_table_indexes($tab));

?>
--EXPECT--
Array
(
    [0] => Array
        (
            [num] => 0
            [name] => PrimaryKey
            [type] => 1
            [rows] => 0
            [keys] => 1
            [flags] => 9
            [key_col_0] => 1
            [key_col_order_0] => 0
        )

)
