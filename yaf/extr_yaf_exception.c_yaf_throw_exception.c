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
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 long YAF_ERR_BASE ; 
 size_t YAF_EXCEPTION_OFFSET (long) ; 
 int /*<<< orphan*/ ** yaf_buildin_exceptions ; 
 int /*<<< orphan*/ * yaf_exception_ce ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ *,char*,long) ; 

void yaf_throw_exception(long code, char *message) {
	zend_class_entry *base_exception = yaf_exception_ce;

	if ((code & YAF_ERR_BASE) == YAF_ERR_BASE
			&& yaf_buildin_exceptions[YAF_EXCEPTION_OFFSET(code)]) {
		base_exception = yaf_buildin_exceptions[YAF_EXCEPTION_OFFSET(code)];
	}

	zend_throw_exception(base_exception, message, code);
}