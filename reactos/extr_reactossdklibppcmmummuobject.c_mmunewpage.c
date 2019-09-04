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
typedef  int /*<<< orphan*/  ppc_map_t ;
typedef  int /*<<< orphan*/  paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_PAGE_ADDR (int /*<<< orphan*/ *) ; 
 int PpcPageTable ; 
 int /*<<< orphan*/ * allocpage () ; 

paddr_t mmunewpage()
{
    ppc_map_t *PagePtr = allocpage();
    if (!PagePtr) return 0;
    return PPC_PAGE_ADDR(PagePtr - PpcPageTable);
}