#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int num_sorttab; TYPE_1__** addr_sorttab; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_4__ {scalar_t__ tag; } ;
struct TYPE_3__ {TYPE_2__ symt; } ;

/* Variables and functions */
 scalar_t__ SymTagPublicSymbol ; 
 int /*<<< orphan*/  cmp_sorttab_addr (struct module*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_get_address (TYPE_2__*,int /*<<< orphan*/ *) ; 

int symt_get_best_at(struct module* module, int idx_sorttab)
{
    ULONG64 ref_addr;
    int idx_sorttab_orig = idx_sorttab;
    if (module->addr_sorttab[idx_sorttab]->symt.tag == SymTagPublicSymbol)
    {
        symt_get_address(&module->addr_sorttab[idx_sorttab]->symt, &ref_addr);
        while (idx_sorttab > 0 &&
               module->addr_sorttab[idx_sorttab]->symt.tag == SymTagPublicSymbol &&
               !cmp_sorttab_addr(module, idx_sorttab - 1, ref_addr))
            idx_sorttab--;
        if (module->addr_sorttab[idx_sorttab]->symt.tag == SymTagPublicSymbol)
        {
            idx_sorttab = idx_sorttab_orig;
            while (idx_sorttab < module->num_sorttab - 1 &&
                   module->addr_sorttab[idx_sorttab]->symt.tag == SymTagPublicSymbol &&
                   !cmp_sorttab_addr(module, idx_sorttab + 1, ref_addr))
                idx_sorttab++;
        }
        /* if no better symbol fond restore original */
        if (module->addr_sorttab[idx_sorttab]->symt.tag == SymTagPublicSymbol)
            idx_sorttab = idx_sorttab_orig;
    }
    return idx_sorttab;
}