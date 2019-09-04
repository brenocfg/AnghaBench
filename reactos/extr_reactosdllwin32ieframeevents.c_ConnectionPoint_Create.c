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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  iid; int /*<<< orphan*/ * container; scalar_t__ sinks_size; int /*<<< orphan*/ * sinks; TYPE_1__ IConnectionPoint_iface; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  TYPE_2__ ConnectionPoint ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointVtbl ; 
 TYPE_2__* heap_alloc (int) ; 

__attribute__((used)) static void ConnectionPoint_Create(REFIID riid, ConnectionPoint **cp,
                                   IConnectionPointContainer *container)
{
    ConnectionPoint *ret = heap_alloc(sizeof(ConnectionPoint));

    ret->IConnectionPoint_iface.lpVtbl = &ConnectionPointVtbl;

    ret->sinks = NULL;
    ret->sinks_size = 0;
    ret->container = container;

    ret->iid = *riid;

    *cp = ret;
}