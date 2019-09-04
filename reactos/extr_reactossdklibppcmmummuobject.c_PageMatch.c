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
typedef  int vaddr_t ;
struct TYPE_3__ {int pteh; } ;
typedef  TYPE_1__ ppc_pte_t ;

/* Variables and functions */

int PageMatch(vaddr_t addr, ppc_pte_t pte)
{
    int vsid_pte = (pte.pteh >> 7) & 15, api_pte = pte.pteh & 63;
    return 
	(((addr >> 28) & 15) == vsid_pte) &&
	(((addr >> 22) & 63) == api_pte);
}