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
struct TYPE_6__ {int ref; int maxCons; TYPE_1__ IDataAdviseHolder_iface; int /*<<< orphan*/ * delegate; void* remote_connections; void* connections; } ;
typedef  TYPE_1__ IDataAdviseHolder ;
typedef  TYPE_2__ DataAdviseHolder ;

/* Variables and functions */
 int /*<<< orphan*/  DataAdviseHolderImpl_VTable ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int INITIAL_SINKS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static IDataAdviseHolder *DataAdviseHolder_Constructor(void)
{
  DataAdviseHolder* newHolder;

  newHolder = HeapAlloc(GetProcessHeap(), 0, sizeof(DataAdviseHolder));

  newHolder->IDataAdviseHolder_iface.lpVtbl = &DataAdviseHolderImpl_VTable;
  newHolder->ref = 1;
  newHolder->maxCons = INITIAL_SINKS;
  newHolder->connections = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                     newHolder->maxCons * sizeof(*newHolder->connections));
  newHolder->remote_connections = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                                            newHolder->maxCons * sizeof(*newHolder->remote_connections));
  newHolder->delegate = NULL;

  TRACE("returning %p\n", &newHolder->IDataAdviseHolder_iface);
  return &newHolder->IDataAdviseHolder_iface;
}