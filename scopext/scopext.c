/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_scopext.h"

/* If you declare any globals in php_scopext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(scopext)
*/

/* True global resources - no need for thread safety here */
static int le_scopext;

/* {{{ scopext_functions[]
 *
 * Every user visible function must have an entry in scopext_functions[].
 */
zend_function_entry scopext_functions[] = {
	PHP_FE(confirm_scopext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(scopextCalculateDistance,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in scopext_functions[] */
};
/* }}} */

/* {{{ scopext_module_entry
 */
zend_module_entry scopext_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"scopext",
	scopext_functions,
	PHP_MINIT(scopext),
	PHP_MSHUTDOWN(scopext),
	PHP_RINIT(scopext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(scopext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(scopext),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SCOPEXT
ZEND_GET_MODULE(scopext)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("scopext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_scopext_globals, scopext_globals)
    STD_PHP_INI_ENTRY("scopext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_scopext_globals, scopext_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_scopext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_scopext_init_globals(zend_scopext_globals *scopext_globals)
{
	scopext_globals->global_value = 0;
	scopext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(scopext)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(scopext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(scopext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(scopext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(scopext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "scopext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_scopext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_scopext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "scopext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto float scopextCalculateDistance(float , float , float , float )
    */
PHP_FUNCTION(scopextCalculateDistance)
{
	int argc = ZEND_NUM_ARGS();

	double lat1;
	double lng1;
	double lat2;
	double lng2;

	double distance;

	if (zend_parse_parameters(argc TSRMLS_CC, "dddd", &lat1, &lng1, &lat2, &lng2) == FAILURE) {
		return;
	}

	const double PI = 3.1415926;
	const double EARTH_RADIUS = 6378.137;

	double radLat1 = lat1 * PI / 180.0;
	double radLat2 = lat2 * PI / 180.0;
	double a       = radLat1 - radLat2;
	double b       = (lng1 * PI / 180.0) - (lng2 * PI / 180.0);
	double s       = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));

	distance = round(s * EARTH_RADIUS * 1000);
	RETURN_DOUBLE(distance);
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
