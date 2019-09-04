#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;
struct symt_pointer {unsigned long size; TYPE_1__ symt; struct symt* pointsto; } ;
struct symt {int dummy; } ;
struct module {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SymTagPointerType ; 
 struct symt_pointer* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  symt_add_type (struct module*,TYPE_1__*) ; 

struct symt_pointer* symt_new_pointer(struct module* module, struct symt* ref_type, unsigned long size)
{
    struct symt_pointer*        sym;

    if ((sym = pool_alloc(&module->pool, sizeof(*sym))))
    {
        sym->symt.tag = SymTagPointerType;
        sym->pointsto = ref_type;
        sym->size     = size;
        symt_add_type(module, &sym->symt);
    }
    return sym;
}