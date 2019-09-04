#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ppc_pteg_t ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  proc; } ;
typedef  TYPE_1__ ppc_map_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PpcHashedPTE ; 
 size_t PtegNumber (int /*<<< orphan*/ ,int) ; 

ppc_pteg_t *PtegFromPage(ppc_map_t *map, int hfun)
{
    if(!map->proc && !map->addr) return 0;
    return &PpcHashedPTE[PtegNumber(map->addr, hfun)];
}