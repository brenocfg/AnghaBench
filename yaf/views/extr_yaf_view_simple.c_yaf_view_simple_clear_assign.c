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
typedef  int /*<<< orphan*/  yaf_view_t ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_TPLVARS ; 
 int /*<<< orphan*/  ZEND_STRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaf_view_simple_ce ; 
 int /*<<< orphan*/  zend_hash_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_read_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_symtable_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void yaf_view_simple_clear_assign(yaf_view_t *view, zend_string *name) {
	zval *tpl_vars = zend_read_property(yaf_view_simple_ce, view, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_TPLVARS), 1, NULL);
	if (tpl_vars && Z_TYPE_P(tpl_vars) == IS_ARRAY) {
		if (name) {
			zend_symtable_del(Z_ARRVAL_P(tpl_vars), name);
		} else {
			zend_hash_clean(Z_ARRVAL_P(tpl_vars));
		}
	} 
}