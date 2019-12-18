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

/* Variables and functions */
 scalar_t__ IS_ABSOLUTE_PATH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  YAF_ERR_TYPE_ERROR ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_OPTS ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_TPLDIR ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_TPLVARS ; 
 int /*<<< orphan*/  ZEND_STRL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaf_trigger_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yaf_view_simple_ce ; 
 int /*<<< orphan*/  zend_update_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

yaf_view_t *yaf_view_simple_instance(yaf_view_t *this_ptr, zval *tpl_dir, zval *options) /* {{{ */ {
	zval tpl_vars;

	if (Z_ISUNDEF_P(this_ptr)) {
		object_init_ex(this_ptr, yaf_view_simple_ce);
	}

	array_init(&tpl_vars);
	zend_update_property(yaf_view_simple_ce, this_ptr, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_TPLVARS), &tpl_vars);
	zval_ptr_dtor(&tpl_vars);

	if (tpl_dir && Z_TYPE_P(tpl_dir) == IS_STRING) {
		if (IS_ABSOLUTE_PATH(Z_STRVAL_P(tpl_dir), Z_STRLEN_P(tpl_dir))) {
			zend_update_property(yaf_view_simple_ce, this_ptr, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_TPLDIR), tpl_dir);
		} else {
			/* redo the object_init_ex? zval_ptr_dtor(this_ptr); */
			yaf_trigger_error(YAF_ERR_TYPE_ERROR, "Expects an absolute path for templates directory");
			return NULL;
		}
	} 

	if (options && IS_ARRAY == Z_TYPE_P(options)) {
		zend_update_property(yaf_view_simple_ce, this_ptr, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_OPTS), options);
	}

	return this_ptr;
}