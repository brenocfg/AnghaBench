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
typedef  char zend_op_array ;
typedef  int /*<<< orphan*/  zend_array ;
typedef  int /*<<< orphan*/  yaf_view_t ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  YAF_VIEW_PROPERTY_NAME_TPLVARS ; 
 int /*<<< orphan*/  ZEND_STRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_op_array (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  strpprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yaf_view_build_symtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaf_view_destroy_symtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaf_view_exec_tpl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaf_view_simple_ce ; 
 char* zend_compile_string (int /*<<< orphan*/ *,char*) ; 
 char* zend_make_compiled_string_description (char*) ; 
 int /*<<< orphan*/ * zend_read_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

int yaf_view_simple_eval(yaf_view_t *view, zval *tpl, zval * vars, zval *ret) {
	zval *tpl_vars;
	zend_array *symbol_table;

	if (IS_STRING != Z_TYPE_P(tpl)) {
		return 0;
	}

	tpl_vars = zend_read_property(yaf_view_simple_ce, view, ZEND_STRL(YAF_VIEW_PROPERTY_NAME_TPLVARS), 1, NULL);

	symbol_table = yaf_view_build_symtable(tpl_vars, vars);

	if (Z_STRLEN_P(tpl)) {
		zval phtml;
		zend_op_array *op_array;
		char *eval_desc = zend_make_compiled_string_description("template code");
		
		/* eval require code mustn't be wrapped in opening and closing PHP tags */
		ZVAL_STR(&phtml, strpprintf(0, "?>%s", Z_STRVAL_P(tpl)));

		op_array = zend_compile_string(&phtml, eval_desc);

		zval_ptr_dtor(&phtml);
		efree(eval_desc);

		if (op_array) {
			(void)yaf_view_exec_tpl(view, op_array, symbol_table, ret);
			destroy_op_array(op_array);
			efree(op_array);
		}
	}

	yaf_view_destroy_symtable(symbol_table);

	return 1;
}