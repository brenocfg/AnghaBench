#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* iface; } ;
struct TYPE_8__ {int /*<<< orphan*/  defined; TYPE_1__ details; } ;
typedef  TYPE_2__ type_t ;
typedef  int /*<<< orphan*/  statement_list_t ;
struct TYPE_9__ {int /*<<< orphan*/ * async_iface; int /*<<< orphan*/ * disp_inherit; TYPE_2__* inherit; int /*<<< orphan*/ * stmts; int /*<<< orphan*/ * disp_methods; int /*<<< orphan*/ * disp_props; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compute_method_indexes (TYPE_2__*) ; 
 TYPE_3__* xmalloc (int) ; 

void type_interface_define(type_t *iface, type_t *inherit, statement_list_t *stmts)
{
    iface->details.iface = xmalloc(sizeof(*iface->details.iface));
    iface->details.iface->disp_props = NULL;
    iface->details.iface->disp_methods = NULL;
    iface->details.iface->stmts = stmts;
    iface->details.iface->inherit = inherit;
    iface->details.iface->disp_inherit = NULL;
    iface->details.iface->async_iface = NULL;
    iface->defined = TRUE;
    compute_method_indexes(iface);
}