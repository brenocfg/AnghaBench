#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t max_cons; struct TYPE_6__* connections; int /*<<< orphan*/ * pAdvSink; } ;
typedef  TYPE_1__ OleAdviseHolderImpl ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  release_statdata (TYPE_1__*) ; 

__attribute__((used)) static void OleAdviseHolderImpl_Destructor(OleAdviseHolderImpl *This)
{
    DWORD index;
    TRACE("%p\n", This);

    for (index = 0; index < This->max_cons; index++)
    {
        if (This->connections[index].pAdvSink != NULL)
            release_statdata(This->connections + index);
    }

    HeapFree(GetProcessHeap(), 0, This->connections);
    HeapFree(GetProcessHeap(), 0, This);
}