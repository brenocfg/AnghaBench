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
struct module {TYPE_1__** addr_sorttab; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_2__ {int /*<<< orphan*/  symt; } ;

/* Variables and functions */
 int cmp_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cmp_sorttab_addr(struct module* module, int idx, ULONG64 addr)
{
    ULONG64     ref;
    symt_get_address(&module->addr_sorttab[idx]->symt, &ref);
    return cmp_addr(ref, addr);
}