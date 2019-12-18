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
typedef  int /*<<< orphan*/  yaf_view_t ;
typedef  int /*<<< orphan*/  copy_ctor_func_t ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_TPLVARS ; 
 int /*<<< orphan*/  ZEND_STRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaf_view_simple_ce ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_read_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ zval_add_ref ; 

int yaf_view_simple_assign_multi(yaf_view_t *view, zval *value) /* {{{ */ {
	zval *tpl_vars = zend_read_property(yaf_view_simple_ce, view, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_TPLVARS), 1, NULL);
	if (Z_TYPE_P(value) == IS_ARRAY) {
		zend_hash_copy(Z_ARRVAL_P(tpl_vars), Z_ARRVAL_P(value), (copy_ctor_func_t) zval_add_ref);
		return 1;
	}
	return 0;
}