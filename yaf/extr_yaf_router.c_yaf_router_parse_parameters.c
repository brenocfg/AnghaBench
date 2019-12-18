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
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  YAF_ROUTER_URL_DELIMIETER ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 char* php_strtok_r (char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 

void yaf_router_parse_parameters(char *uri, zval *params) {
	char *key, *ptrptr, *tmp, *value;
	zval val;
	uint key_len;

	array_init(params);

	tmp = estrdup(uri);
	key = php_strtok_r(tmp, YAF_ROUTER_URL_DELIMIETER, &ptrptr);
	while (key) {
		key_len = strlen(key);
		if (key_len) {
			value = php_strtok_r(NULL, YAF_ROUTER_URL_DELIMIETER, &ptrptr);
			if (value && strlen(value)) {
				ZVAL_STRING(&val, value);
			} else {
				ZVAL_NULL(&val);
			}
			zend_hash_str_update(Z_ARRVAL_P(params), key, key_len, &val);
		}

		key = php_strtok_r(NULL, YAF_ROUTER_URL_DELIMIETER, &ptrptr);
	}

	efree(tmp);
}