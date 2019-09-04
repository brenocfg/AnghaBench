#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ addr; scalar_t__ proc; } ;
typedef  TYPE_1__ ppc_map_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ MmuFreePage ;

/* Variables and functions */
 TYPE_2__* FreeList ; 

void freepage(ppc_map_t *PagePtr)
{
    MmuFreePage *FreePage = (MmuFreePage*)PagePtr;
    PagePtr->proc = PagePtr->addr = 0;
    FreePage->next = FreeList;
    FreeList = FreePage;
}