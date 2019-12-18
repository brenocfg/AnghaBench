#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int /*<<< orphan*/  scope; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_11__ {int /*<<< orphan*/ * symbol_table; } ;
typedef  TYPE_2__ zend_execute_data ;
typedef  int /*<<< orphan*/  zend_array ;
typedef  int /*<<< orphan*/  yaf_view_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  PHP_OUTPUT_HANDLER_STDFLAGS ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ UNEXPECTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ADD_CALL_FLAG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ZEND_CALL_HAS_SYMBOL_TABLE ; 
 int ZEND_CALL_NESTED_CODE ; 
 int /*<<< orphan*/  ZEND_CALL_TOP ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  php_error_docref (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ php_output_discard () ; 
 int /*<<< orphan*/  php_output_end () ; 
 scalar_t__ php_output_get_contents (int /*<<< orphan*/ *) ; 
 scalar_t__ php_output_start_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_execute_ex (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_init_execute_data (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_vm_stack_free_call_frame (TYPE_2__*) ; 
 TYPE_2__* zend_vm_stack_push_call_frame (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yaf_view_exec_tpl(yaf_view_t *view, zend_op_array *op_array, zend_array *symbol_table, zval* ret) /* {{{ */ {
	zend_execute_data *call;
	zval result;

	ZVAL_UNDEF(&result);

	op_array->scope = Z_OBJCE_P(view);

	call = zend_vm_stack_push_call_frame(ZEND_CALL_NESTED_CODE
#if PHP_VERSION_ID >= 70100
		    | ZEND_CALL_HAS_SYMBOL_TABLE
#endif
			,
			(zend_function*)op_array, 0, op_array->scope, Z_OBJ_P(view));

	call->symbol_table = symbol_table;

	if (ret && php_output_start_user(NULL, 0, PHP_OUTPUT_HANDLER_STDFLAGS) == FAILURE) {
		php_error_docref("ref.outcontrol", E_WARNING, "failed to create buffer");
		return 0;
	}

	zend_init_execute_data(call, op_array, &result);

	ZEND_ADD_CALL_FLAG(call, ZEND_CALL_TOP);
	zend_execute_ex(call);
	zend_vm_stack_free_call_frame(call);

	zval_ptr_dtor(&result);

	if (UNEXPECTED(EG(exception) != NULL)) {
		if (ret) {
			php_output_discard();
		}
		return 0;
	}

	if (ret) {
		if (php_output_get_contents(ret) == FAILURE) {
			php_output_end();
			php_error_docref(NULL, E_WARNING, "Unable to fetch ob content");
			return 0;
		}

		if (php_output_discard() != SUCCESS ) {
			return 0;
		}
	}

	return 1;
}