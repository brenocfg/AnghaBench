#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var_list_t ;
struct TYPE_6__ {TYPE_3__* iface; } ;
struct TYPE_7__ {int /*<<< orphan*/  defined; TYPE_1__ details; } ;
typedef  TYPE_2__ type_t ;
struct TYPE_8__ {int /*<<< orphan*/ * async_iface; int /*<<< orphan*/ * disp_inherit; int /*<<< orphan*/  inherit; int /*<<< orphan*/ * stmts; int /*<<< orphan*/ * disp_methods; int /*<<< orphan*/ * disp_props; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compute_method_indexes (TYPE_2__*) ; 
 int /*<<< orphan*/  error_loc (char*) ; 
 int /*<<< orphan*/  find_type (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* xmalloc (int) ; 

void type_dispinterface_define(type_t *iface, var_list_t *props, var_list_t *methods)
{
    iface->details.iface = xmalloc(sizeof(*iface->details.iface));
    iface->details.iface->disp_props = props;
    iface->details.iface->disp_methods = methods;
    iface->details.iface->stmts = NULL;
    iface->details.iface->inherit = find_type("IDispatch", NULL, 0);
    if (!iface->details.iface->inherit) error_loc("IDispatch is undefined\n");
    iface->details.iface->disp_inherit = NULL;
    iface->details.iface->async_iface = NULL;
    iface->defined = TRUE;
    compute_method_indexes(iface);
}