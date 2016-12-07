--TEST--
mdb_version() function
--SKIPIF--
<?php 

if(!extension_loaded('mdbtools')) die('skip ');

 ?>
--FILE--
<?php
$mdb = mdb_open("test.mdb") or die("Failed");

$version = mdb_version($mdb);

switch ($version)
{
  case MDB_VER_JET3:
  case MDB_VER_JET4:
    echo "OK";
    break;
  default: 
    echo "Unknown version: $version";
    break;
}

?>
--EXPECT--
OK
