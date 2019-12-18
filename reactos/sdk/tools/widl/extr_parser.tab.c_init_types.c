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

/* Variables and functions */
 int /*<<< orphan*/  TYPE_BASIC_BYTE ; 
 int /*<<< orphan*/  TYPE_BASIC_DOUBLE ; 
 int /*<<< orphan*/  TYPE_BASIC_ERROR_STATUS_T ; 
 int /*<<< orphan*/  TYPE_BASIC_FLOAT ; 
 int /*<<< orphan*/  TYPE_BASIC_HANDLE ; 
 int /*<<< orphan*/  TYPE_BASIC_WCHAR ; 
 int /*<<< orphan*/  decl_builtin_alias (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_builtin_basic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_new_basic (int /*<<< orphan*/ ) ; 

void init_types(void)
{
  decl_builtin_basic("byte", TYPE_BASIC_BYTE);
  decl_builtin_basic("wchar_t", TYPE_BASIC_WCHAR);
  decl_builtin_basic("float", TYPE_BASIC_FLOAT);
  decl_builtin_basic("double", TYPE_BASIC_DOUBLE);
  decl_builtin_basic("error_status_t", TYPE_BASIC_ERROR_STATUS_T);
  decl_builtin_basic("handle_t", TYPE_BASIC_HANDLE);
  decl_builtin_alias("boolean", type_new_basic(TYPE_BASIC_BYTE));
}