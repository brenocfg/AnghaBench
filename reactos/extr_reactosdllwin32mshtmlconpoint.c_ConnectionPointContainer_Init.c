#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpc_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * forward_container; int /*<<< orphan*/ * outer; int /*<<< orphan*/ * cps; int /*<<< orphan*/  const* cp_entries; TYPE_1__ IConnectionPointContainer_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ ConnectionPointContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainerVtbl ; 

void ConnectionPointContainer_Init(ConnectionPointContainer *This, IUnknown *outer, const cpc_entry_t *cp_entries)
{
    This->IConnectionPointContainer_iface.lpVtbl = &ConnectionPointContainerVtbl;
    This->cp_entries = cp_entries;
    This->cps = NULL;
    This->outer = outer;
    This->forward_container = NULL;
}