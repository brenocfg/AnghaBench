#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_bool ;
typedef  int /*<<< orphan*/  yaf_route_t ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yaf_route_map_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yaf_route_regex_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yaf_route_rewrite_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yaf_route_simple_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * yaf_route_supervar_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_is_true (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 

yaf_route_t * yaf_route_instance(yaf_route_t *this_ptr, zval *config) {
	zval *match, *def, *map, *verify, *reverse, *pzval;
	yaf_route_t *instance = NULL;

	if (!config || IS_ARRAY != Z_TYPE_P(config)) {
		return NULL;
	}

	if ((pzval = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("type"))) == NULL ||
		IS_STRING != Z_TYPE_P(pzval)) {
		return NULL;
	}

	if (zend_string_equals_literal_ci(Z_STR_P(pzval), "rewrite")) {
		if ((match = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("match"))) == NULL ||
			Z_TYPE_P(match) != IS_STRING) {
			return NULL;
		}
		if ((def = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("route"))) == NULL ||
			Z_TYPE_P(def) != IS_ARRAY) {
			return NULL;
		}

		if ((verify = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("route"))) == NULL ||
			Z_TYPE_P(verify) != IS_ARRAY) {
			verify = NULL;
		}

        instance = yaf_route_rewrite_instance(this_ptr, match, def, verify);
	} else if (zend_string_equals_literal_ci(Z_STR_P(pzval), "regex")) {
		if ((match = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("match"))) == NULL ||
			Z_TYPE_P(match) != IS_STRING) {
			return NULL;
		}
		if ((def = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("route"))) == NULL ||
			Z_TYPE_P(def) != IS_ARRAY) {
			return NULL;
		}
		if ((map = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("map"))) == NULL ||
			Z_TYPE_P(map) != IS_ARRAY) {
			map = NULL;
		}

		if ((verify = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("route"))) == NULL ||
			Z_TYPE_P(verify) != IS_ARRAY) {
			verify = NULL;
		}

		if ((reverse = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("route"))) == NULL ||
			Z_TYPE_P(reverse) != IS_STRING) {
			reverse = NULL;
		}

		instance = yaf_route_regex_instance(this_ptr, match, def, map, verify, reverse);
	} else if (zend_string_equals_literal_ci(Z_STR_P(pzval), "map")) {
		zend_string *delimiter = NULL;
		zend_bool controller_prefer = 0;
		
		if ((pzval = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("controllerPrefer"))) != NULL) {
			controller_prefer = zend_is_true(pzval);
		}

		if ((pzval = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("delimiter"))) != NULL
			&& Z_TYPE_P(pzval) == IS_STRING) {
			delimiter = Z_STR_P(pzval);
		}

		instance = yaf_route_map_instance(this_ptr, controller_prefer, delimiter);
	} else if (zend_string_equals_literal_ci(Z_STR_P(pzval), "simple")) {
		if ((match = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("module"))) == NULL ||
			Z_TYPE_P(match) != IS_STRING) {
			return NULL;
		}
		if ((def = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("controller"))) == NULL ||
			Z_TYPE_P(def) != IS_STRING) {
			return NULL;
		}
		if ((map = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("action"))) == NULL ||
			Z_TYPE_P(map) != IS_STRING) {
			return NULL;
		}

		instance = yaf_route_simple_instance(this_ptr, match, def, map);
	} else if (zend_string_equals_literal_ci(Z_STR_P(pzval), "supervar")) {
		if ((match = zend_hash_str_find(Z_ARRVAL_P(config), ZEND_STRL("varname"))) == NULL ||
			Z_TYPE_P(match) != IS_STRING) {
			return NULL;
		}

		instance = yaf_route_supervar_instance(this_ptr, match);
	}

	return instance;
}