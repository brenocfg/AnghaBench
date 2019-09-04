#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ var_t ;
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IN ; 
 int /*<<< orphan*/  append_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_type_or_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_func_handle_var (int /*<<< orphan*/  const*,TYPE_1__*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  make_attr (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_function_add_head_arg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void add_explicit_handle_if_necessary(const type_t *iface, var_t *func)
{
    unsigned char explicit_fc, implicit_fc;

    /* check for a defined binding handle */
    if (!get_func_handle_var( iface, func, &explicit_fc, &implicit_fc ) || !explicit_fc)
    {
        /* no explicit handle specified so add
         * "[in] handle_t IDL_handle" as the first parameter to the
         * function */
        var_t *idl_handle = make_var(xstrdup("IDL_handle"));
        idl_handle->attrs = append_attr(NULL, make_attr(ATTR_IN));
        idl_handle->type = find_type_or_error("handle_t", 0);
        type_function_add_head_arg(func->type, idl_handle);
    }
}