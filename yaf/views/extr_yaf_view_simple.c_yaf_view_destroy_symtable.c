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
typedef  int /*<<< orphan*/  zend_array ;

/* Variables and functions */
 int /*<<< orphan*/  zend_array_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void yaf_view_destroy_symtable(zend_array *symbol_table) /* {{{ */ {
	zend_array_destroy(symbol_table);
}