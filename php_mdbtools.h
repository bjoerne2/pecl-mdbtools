/*
   +----------------------------------------------------------------------+
   | This library is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU Lesser General Public           |
   | License as published by the Free Software Foundation; either         |
   | version 2.1 of the License, or (at your option) any later version.   | 
   |                                                                      |
   | This library is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
   | Lesser General Public License for more details.                      | 
   |                                                                      |
   | You should have received a copy of the GNU Lesser General Public     |
   | License in the file LICENSE along with this library;                 |
   | if not, write to the                                                 | 
   |                                                                      |
   |   Free Software Foundation, Inc.,                                    |
   |   59 Temple Place, Suite 330,                                        |
   |   Boston, MA  02111-1307  USA                                        |
   +----------------------------------------------------------------------+
   | Authors: Hartmut Holzgraefe <hartmut@php.net>                        |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#ifndef PHP_MDBTOOLS_H
#define PHP_MDBTOOLS_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_MDBTOOLS
#define PHP_MDBTOOLS_VERSION "1.0.0"


#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#include <mdbtools.h>
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry mdbtools_module_entry;
#define phpext_mdbtools_ptr &mdbtools_module_entry

#ifdef PHP_WIN32
#define PHP_MDBTOOLS_API __declspec(dllexport)
#else
#define PHP_MDBTOOLS_API
#endif

PHP_MINIT_FUNCTION(mdbtools);
PHP_MSHUTDOWN_FUNCTION(mdbtools);
PHP_RINIT_FUNCTION(mdbtools);
PHP_RSHUTDOWN_FUNCTION(mdbtools);
PHP_MINFO_FUNCTION(mdbtools);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


PHP_FUNCTION(mdb_open);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_open_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_open_arg_info NULL
#endif

PHP_FUNCTION(mdb_close);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_close_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_close_arg_info NULL
#endif

PHP_FUNCTION(mdb_version);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_version_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_version_arg_info NULL
#endif

PHP_FUNCTION(mdb_tables);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_tables_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, db)
  ZEND_ARG_INFO(0, systabs)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_tables_arg_info NULL
#endif

PHP_FUNCTION(mdb_table_open);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_table_open_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, db)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_table_open_arg_info NULL
#endif

PHP_FUNCTION(mdb_fetch_row);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_fetch_row_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_fetch_row_arg_info NULL
#endif

PHP_FUNCTION(mdb_fetch_assoc);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_fetch_assoc_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_fetch_assoc_arg_info NULL
#endif

PHP_FUNCTION(mdb_rewind);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_rewind_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_rewind_arg_info NULL
#endif

PHP_FUNCTION(mdb_table_close);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_table_close_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_table_close_arg_info NULL
#endif

PHP_FUNCTION(mdb_num_fields);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_num_fields_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_num_fields_arg_info NULL
#endif

PHP_FUNCTION(mdb_num_rows);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_num_rows_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_num_rows_arg_info NULL
#endif

PHP_FUNCTION(mdb_table_fields);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_table_fields_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_table_fields_arg_info NULL
#endif

PHP_FUNCTION(mdb_table_indexes);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_table_indexes_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_table_indexes_arg_info NULL
#endif

PHP_FUNCTION(mdb_type_name);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(mdb_type_name_arg_info, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, db)
  ZEND_ARG_INFO(0, typecode)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define mdb_type_name_arg_info NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

/* 'bottom' header snippets*/
typedef struct {
	MdbTableDef *table;
	int num_cols;
	char **bound_values;
	int   *bound_lengths;
	char **column_names;
} my_MdbTableDef;

#endif /* PHP_HAVE_MDBTOOLS */

#endif /* PHP_MDBTOOLS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
