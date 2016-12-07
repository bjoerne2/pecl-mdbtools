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

#include "php_mdbtools.h"

#if HAVE_MDBTOOLS

/* {{{ Resource destructors */
int le_MdbDatabase;
void MdbDatabase_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	MdbHandle * resource = (MdbHandle *)(rsrc->ptr);

	do {
		mdb_close(resource);
	} while (0);
}

int le_MdbTable;
void MdbTable_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	my_MdbTableDef * resource = (my_MdbTableDef *)(rsrc->ptr);

	do {
		int i;

		for (i = 0; i < resource->num_cols; i++) {
		  efree(resource->bound_values[i]);
		}
		efree(resource->column_names);
		efree(resource->bound_values);

		mdb_free_tabledef(resource->table);
	} while (0);

	efree(resource);
}

/* }}} */

/* {{{ mdbtools_functions[] */
zend_function_entry mdbtools_functions[] = {
	PHP_FE(mdb_open            , mdb_open_arg_info)
	PHP_FE(mdb_close           , mdb_close_arg_info)
	PHP_FE(mdb_version         , mdb_version_arg_info)
	PHP_FE(mdb_tables          , mdb_tables_arg_info)
	PHP_FE(mdb_table_open      , mdb_table_open_arg_info)
	PHP_FE(mdb_fetch_row       , mdb_fetch_row_arg_info)
	PHP_FE(mdb_fetch_assoc     , mdb_fetch_assoc_arg_info)
	PHP_FE(mdb_rewind          , mdb_rewind_arg_info)
	PHP_FE(mdb_table_close     , mdb_table_close_arg_info)
	PHP_FE(mdb_num_fields      , mdb_num_fields_arg_info)
	PHP_FE(mdb_num_rows        , mdb_num_rows_arg_info)
	PHP_FE(mdb_table_fields    , mdb_table_fields_arg_info)
	PHP_FE(mdb_table_indexes   , mdb_table_indexes_arg_info)
	PHP_FE(mdb_type_name       , mdb_type_name_arg_info)
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ mdbtools_module_entry
 */
zend_module_entry mdbtools_module_entry = {
	STANDARD_MODULE_HEADER,
	"mdbtools",
	mdbtools_functions,
	PHP_MINIT(mdbtools),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(mdbtools), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(mdbtools),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(mdbtools), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(mdbtools),
	PHP_MDBTOOLS_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MDBTOOLS
ZEND_GET_MODULE(mdbtools)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mdbtools)
{
	REGISTER_LONG_CONSTANT("MDB_VER_JET3", MDB_VER_JET3, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_VER_JET4", MDB_VER_JET4, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_BOOL", MDB_BOOL, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_BYTE", MDB_BYTE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_INT", MDB_INT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_LONGINT", MDB_LONGINT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_MONEY", MDB_MONEY, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_FLOAT", MDB_FLOAT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_DOUBLE", MDB_DOUBLE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_SDATETIME", MDB_SDATETIME, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_TEXT", MDB_TEXT, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_OLE", MDB_OLE, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_MEMO", MDB_MEMO, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_REPID", MDB_REPID, CONST_PERSISTENT | CONST_CS);
	REGISTER_LONG_CONSTANT("MDB_NUMERIC", MDB_NUMERIC, CONST_PERSISTENT | CONST_CS);
	le_MdbDatabase = zend_register_list_destructors_ex(MdbDatabase_dtor, 
						   NULL, "MdbDatabase", module_number);
	le_MdbTable = zend_register_list_destructors_ex(MdbTable_dtor, 
						   NULL, "MdbTable", module_number);
	do {
		mdb_init();
	} while (0);

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(mdbtools)
{
	do {
		mdb_exit();
	} while (0);

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(mdbtools)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(mdbtools)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(mdbtools)
{
	php_printf("MDB data file access library\n");
	php_info_print_table_start();
	php_info_print_table_row(2, "Version",PHP_MDBTOOLS_VERSION " (stable)");
	php_info_print_table_row(2, "Released", "2007-11-27");
	php_info_print_table_row(2, "CVS Revision", "$Id: mdbtools.c 297236 2010-03-31 20:39:48Z johannes $");
	php_info_print_table_row(2, "Authors", "Hartmut Holzgraefe 'hartmut@php.net' (lead)\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */


/* {{{ proto resource MdbDatabase mdb_open(string path)
  Open an Access .mdb file for reading */
PHP_FUNCTION(mdb_open)
{
	MdbHandle * return_res;
	long return_res_id = -1;

	const char * path = NULL;
	int path_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		return;
	}

	do {
#if HAVE_MDB_OPEN_TWO_PARAMS
		return_res = mdb_open((char *)path, MDB_NOFLAGS);
#else
		return_res = mdb_open((char *)path);
#endif

		if (!return_res) RETURN_FALSE;
	} while (0);

	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_MdbDatabase);
}
/* }}} mdb_open */


/* {{{ proto void mdb_close(resource MdbDatabase db)
  Close an open Access .mdb file */
PHP_FUNCTION(mdb_close)
{
	zval * db_res = NULL;
	int db_resid = -1;
	MdbHandle * db;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &db_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(db, MdbHandle *, &db_res, db_resid, "MdbDatabase", le_MdbDatabase);



	do {
		FREE_RESOURCE(db_res); 
	} while (0);
}
/* }}} mdb_close */


/* {{{ proto int mdb_version(resource MdbDatabase db)
  Get Jet Engine version number from .mdb file */
PHP_FUNCTION(mdb_version)
{
	zval * db_res = NULL;
	int db_resid = -1;
	MdbHandle * db;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &db_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(db, MdbHandle *, &db_res, db_resid, "MdbDatabase", le_MdbDatabase);



	do {
		RETURN_LONG(db->f->jet_version);
	} while (0);
}
/* }}} mdb_version */


/* {{{ proto array mdb_tables(resource MdbDatabase db[, bool systabs])
  Get names of tables in an .mdb file */
PHP_FUNCTION(mdb_tables)
{
	zval * db_res = NULL;
	int db_resid = -1;
	MdbHandle * db;

	zend_bool systabs = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|b", &db_res, &systabs) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(db, MdbHandle *, &db_res, db_resid, "MdbDatabase", le_MdbDatabase);



	array_init(return_value);

	do {
		int i;
		MdbCatalogEntry *entry;

		/* read the catalog */
		if (NULL == mdb_read_catalog (db, MDB_TABLE)) RETURN_FALSE;

		array_init(return_value);

		/* loop over each entry in the catalog */
		for (i=0; i < db->num_catalog; i++) {
		  entry = g_ptr_array_index (db->catalog, i);
			  
		  if (!systabs && !strncmp("MSys", entry->object_name, 4)) {
			  continue;
		  }
		  add_next_index_string(return_value, entry->object_name, 1);
		}
	} while (0);
}
/* }}} mdb_tables */


/* {{{ proto resource MdbTable mdb_table_open(resource MdbDatabase db, string table)
  Open a table in an .mdb file for reading */
PHP_FUNCTION(mdb_table_open)
{
	my_MdbTableDef * return_res = (my_MdbTableDef *)ecalloc(1, sizeof(my_MdbTableDef));
	long return_res_id = -1;
	zval * db_res = NULL;
	int db_resid = -1;
	MdbHandle * db;

	const char * table = NULL;
	int table_len = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &db_res, &table, &table_len) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(db, MdbHandle *, &db_res, db_resid, "MdbDatabase", le_MdbDatabase);



	do {
		int i, j;
		MdbCatalogEntry *entry;
		MdbColumn *col;
 
		mdb_read_catalog(db, MDB_TABLE);

		return_res->table = NULL;

		for (i=0;i<db->num_catalog;i++) {
			entry = g_ptr_array_index(db->catalog,i);
			if (!strcmp(entry->object_name, table)) {
				return_res->table = mdb_read_table(entry);
				if (!return_res->table) RETURN_FALSE;

				return_res->num_cols = return_res->table->num_cols;

				mdb_read_columns(return_res->table);
				mdb_read_indices(return_res->table);
				mdb_rewind_table(return_res->table); 

				return_res->column_names  = ecalloc(return_res->num_cols, sizeof(char *));
				return_res->bound_values  = ecalloc(return_res->num_cols, sizeof(char *));
				return_res->bound_lengths = ecalloc(return_res->num_cols, sizeof(int));

				for (j=0; j<return_res->num_cols; j++) {
					col=g_ptr_array_index(return_res->table->columns, j);

					return_res->column_names[j] = col->name;
   
					return_res->bound_values[j] = emalloc(MDB_BIND_SIZE);
					return_res->bound_values[j][0] = '\0';
#if HAVE_MDB_BIND_COLUMN_FOUR_PARAMS
					mdb_bind_column(return_res->table, j+1, return_res->bound_values[j], return_res->bound_lengths+j);
#else
					mdb_bind_column(return_res->table, j+1, return_res->bound_values[j]);
#endif
				}
			}
		}

		if (!return_res->table) RETURN_FALSE;
	} while (0);

	return_res_id = ZEND_REGISTER_RESOURCE(return_value, return_res, le_MdbTable);
}
/* }}} mdb_table_open */


/* {{{ proto array mdb_fetch_row(resource MdbTable table)
  Get a table row as an enumerated array */
PHP_FUNCTION(mdb_fetch_row)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	array_init(return_value);

	do {
		int i;

		if (!mdb_fetch_row(table->table)) {
			RETURN_FALSE;
		}

		array_init(return_value);

		for (i = 0; i < table->num_cols; i++) {
			add_next_index_stringl(return_value, table->bound_values[i], table->bound_lengths[i], 1);
		}
	} while (0);
}
/* }}} mdb_fetch_row */


/* {{{ proto array mdb_fetch_assoc(resource MdbTable table)
  Get a table row as an associative array */
PHP_FUNCTION(mdb_fetch_assoc)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	array_init(return_value);

	do {
		int i;

		if (!mdb_fetch_row(table->table)) {
			RETURN_FALSE;
		}

		array_init(return_value);

		for (i = 0; i < table->num_cols; i++) {
			add_assoc_stringl(return_value, table->column_names[i], table->bound_values[i], table->bound_lengths[i], 1);
		}
	} while (0);
}
/* }}} mdb_fetch_assoc */


/* {{{ proto int mdb_rewind(resource MdbTable table)
  Rewind to first row in table */
PHP_FUNCTION(mdb_rewind)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	do {
		RETURN_LONG(mdb_rewind_table(table->table));
	} while (0);
}
/* }}} mdb_rewind */


/* {{{ proto void mdb_table_close(resource MdbTable table)
  Close an opened table */
PHP_FUNCTION(mdb_table_close)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	do {
		FREE_RESOURCE(table_res); 
	} while (0);
}
/* }}} mdb_table_close */


/* {{{ proto int mdb_num_fields(resource MdbTable table)
  Get number of table columns */
PHP_FUNCTION(mdb_num_fields)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	do {
		RETURN_LONG(table->table->num_cols);
	} while (0);
}
/* }}} mdb_num_fields */


/* {{{ proto int mdb_num_rows(resource MdbTable table)
  Get number of table rows */
PHP_FUNCTION(mdb_num_rows)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	do {
		RETURN_LONG(table->table->num_rows);
	} while (0);
}
/* }}} mdb_num_rows */


/* {{{ proto array mdb_table_fields(resource MdbTable table)
  Get field type information for all fields in a table */
PHP_FUNCTION(mdb_table_fields)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	array_init(return_value);

	do {
		int i;
		zval *row;
		MdbColumn *col;

		array_init(return_value);
		
		for (i = 0; i < table->table->num_cols; i++)
		{
		   MAKE_STD_ZVAL(row);
		   array_init(row);

		   col = g_ptr_array_index (table->table->columns, i);

		   add_assoc_string(row, "name", col->name, 1);
		   add_assoc_long(row, "type", col->col_type);
		   add_assoc_long(row, "size", col->col_size);
		   add_assoc_long(row, "prec", col->col_prec);
		   add_assoc_long(row, "scale", col->col_scale);
		   add_assoc_long(row, "isfixed", col->is_fixed);

		   add_next_index_zval(return_value, row);
		}
	} while (0);
}
/* }}} mdb_table_fields */


/* {{{ proto array mdb_table_indexes(resource MdbTable table)
  Get index type information for all indexes in a table */
PHP_FUNCTION(mdb_table_indexes)
{
	zval * table_res = NULL;
	int table_resid = -1;
	my_MdbTableDef * table;




	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &table_res) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(table, my_MdbTableDef *, &table_res, table_resid, "MdbTable", le_MdbTable);



	array_init(return_value);

	do {
		int i,j;
		zval *row;
		MdbIndex *idx;
		char buf[256];

		array_init(return_value);
		
		for (i = 0; i < table->table->num_idxs; i++)
		{
		   MAKE_STD_ZVAL(row);
		   array_init(row);

		   idx = g_ptr_array_index (table->table->indices, i);

		   add_assoc_long(  row, "num",   idx->index_num);
		   add_assoc_string(row, "name",  idx->name, 1);
		   add_assoc_long(  row, "type",  idx->index_type);
		   add_assoc_long(  row, "rows",  idx->num_rows);
		   add_assoc_long(  row, "keys",  idx->num_keys);
		   add_assoc_long(  row, "flags", idx->flags);

		   for (j=0; j < idx->num_keys; j++) {
			 sprintf(buf, "key_col_%d", j);
			 add_assoc_long(row, buf, idx->key_col_num[j]);
			 sprintf(buf, "key_col_order_%d", j);
			 add_assoc_long(row, buf, idx->key_col_order[j]);
		   }

		   add_next_index_zval(return_value, row);
		}
	} while (0);
}
/* }}} mdb_table_indexes */


/* {{{ proto string mdb_type_name(resource MdbDatabase db, int typecode)
  Look up the name for a field type */
PHP_FUNCTION(mdb_type_name)
{
	zval * db_res = NULL;
	int db_resid = -1;
	MdbHandle * db;

	long typecode = 0;



	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &db_res, &typecode) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(db, MdbHandle *, &db_res, db_resid, "MdbDatabase", le_MdbDatabase);



	do {
		RETURN_STRING(mdb_get_coltype_string (db->default_backend, typecode), 1);
	} while (0);
}
/* }}} mdb_type_name */

#endif /* HAVE_MDBTOOLS */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
