#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t maxCons; int advf; struct TYPE_7__* connections; struct TYPE_7__* remote_connections; scalar_t__ delegate; int /*<<< orphan*/ * pAdvSink; } ;
typedef  TYPE_1__ DataAdviseHolder ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDataObject_DUnadvise (scalar_t__,TYPE_1__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int WINE_ADVF_REMOTE ; 
 int /*<<< orphan*/  release_statdata (TYPE_1__*) ; 

__attribute__((used)) static void DataAdviseHolder_Destructor(DataAdviseHolder* ptrToDestroy)
{
  DWORD index;
  TRACE("%p\n", ptrToDestroy);

  for (index = 0; index < ptrToDestroy->maxCons; index++)
  {
    if (ptrToDestroy->connections[index].pAdvSink != NULL)
    {
      if (ptrToDestroy->delegate && 
          (ptrToDestroy->connections[index].advf & WINE_ADVF_REMOTE))
        IDataObject_DUnadvise(ptrToDestroy->delegate,
          ptrToDestroy->remote_connections[index]);

      release_statdata(ptrToDestroy->connections + index);
    }
  }

  HeapFree(GetProcessHeap(), 0, ptrToDestroy->remote_connections);
  HeapFree(GetProcessHeap(), 0, ptrToDestroy->connections);
  HeapFree(GetProcessHeap(), 0, ptrToDestroy);
}