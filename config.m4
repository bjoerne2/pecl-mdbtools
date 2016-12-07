dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(mdbtools, mdbtools installation prefix,[  --with-mdbtools[=DIR] With mdbtools support])


if test "$PHP_MDBTOOLS" != "no"; then
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

  if test $PKG_CONFIG = "no"; then
	   AC_MSG_ERROR("pkg-config not found")
  fi

  if ! $PKG_CONFIG glib-2.0; then
	   AC_MSG_ERROR("glib-2.0 not found by pkg-config")
  fi

  GLIB_INCS=`$PKG_CONFIG --cflags-only-I glib-2.0`
  PHP_EVAL_INCLINE($GLIB_INCS)
  CPPFLAGS="$CFLAGS $GLIB_INCS"
  CFLAGS="$CFLAGS $GLIB_INCS"

  GLIB_LIBS=`$PKG_CONFIG --libs glib-2.0`' -lm'
  PHP_EVAL_LIBLINE($GLIB_LIBS)
  LDFLAGS="$CFLAGS $GLIB_LIBS"



  if test -r "$PHP_MDBTOOLS/include/mdbtools.h"; then
	PHP_MDBTOOLS_DIR="$PHP_MDBTOOLS"
  else
	AC_MSG_CHECKING(for mdbtools in default path)
	for i in /usr /usr/local; do
	  if test -r "$i/include/mdbtools.h"; then
		PHP_MDBTOOLS_DIR=$i
		AC_MSG_RESULT(found in $i)
		break
	  fi
	done
	if test "x" = "x$PHP_MDBTOOLS_DIR"; then
	  AC_MSG_ERROR(not found)
	fi
  fi

  PHP_ADD_INCLUDE($PHP_MDBTOOLS_DIR/include)

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_MDBTOOLS"
  AC_CHECK_HEADER([mdbtools.h], [], AC_MSG_ERROR('mdbtools.h' header not found))
  PHP_SUBST(MDBTOOLS_SHARED_LIBADD)


  PHP_CHECK_LIBRARY(mdb, mdb_init,
  [
	PHP_ADD_LIBRARY_WITH_PATH(mdb, $PHP_MDBTOOLS_DIR/lib, MDBTOOLS_SHARED_LIBADD)
  ],[
	AC_MSG_ERROR([wrong mdb lib version or lib not found])
  ],[
	-L$PHP_MDBTOOLS_DIR/lib
  ])
  export CPPFLAGS="$OLD_CPPFLAGS"

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_MDBTOOLS"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 40000
#error  this extension requires at least PHP version 4.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 4.0.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(MDBTOOLS_SHARED_LIBADD)
  AC_DEFINE(HAVE_MDBTOOLS, 1, [ ])

  PHP_NEW_EXTENSION(mdbtools, mdbtools.c , $ext_shared)
  AC_MSG_CHECKING([whether mdb_open() takes one or two parameters])
  OLD_CFLAGS=$CFLAGS
  CFLAGS="$CFLAGS -I$PHP_MDBTOOLS_DIR/include"
  AC_TRY_COMPILE([#include <mdbtools.h>], [mdb_open("foo", MDB_NOFLAGS);], RESULT="two", RESULT="one")
  if test "$RESULT" = "two"
  then
	AC_DEFINE(HAVE_MDB_OPEN_TWO_PARAMS, 1, [mdb_open() takes one or two parameters depending on the API version])  
  fi
  CFLAGS=$OLD_CFLAGS
  AC_MSG_RESULT($RESULT)

  AC_MSG_CHECKING([whether mdb_bind_column() takes three or four parameters])
  OLD_CFLAGS=$CFLAGS
  CFLAGS="$CFLAGS -I$PHP_MDBTOOLS_DIR/include"
  AC_TRY_COMPILE([#include <mdbtools.h>], [mdb_bind_column(NULL, 1, NULL, NULL);], RESULT="four", RESULT="three")
  if test "$RESULT" = "four"
  then
	AC_DEFINE(HAVE_MDB_BIND_COLUMN_FOUR_PARAMS, 1, [mdb_bind_column() takes three or four parameters depending on the API version])  
  fi
  CFLAGS=$OLD_CFLAGS
  AC_MSG_RESULT($RESULT)


fi

