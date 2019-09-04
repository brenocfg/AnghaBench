#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int nextCookie; TYPE_3__ IGlobalInterfaceTable_iface; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ StdGlobalInterfaceTableImpl ;
typedef  int /*<<< orphan*/  IGlobalInterfaceTable ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StdGlobalInterfaceTableImpl_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * std_git ; 

IGlobalInterfaceTable* get_std_git(void)
{
  if (!std_git)
  {
    StdGlobalInterfaceTableImpl* newGIT;

    newGIT = HeapAlloc(GetProcessHeap(), 0, sizeof(StdGlobalInterfaceTableImpl));
    if (!newGIT) return NULL;

    newGIT->IGlobalInterfaceTable_iface.lpVtbl = &StdGlobalInterfaceTableImpl_Vtbl;
    list_init(&newGIT->list);
    newGIT->nextCookie = 0xf100; /* that's where windows starts, so that's where we start */

    if (InterlockedCompareExchangePointer((void**)&std_git, &newGIT->IGlobalInterfaceTable_iface, NULL))
    {
      HeapFree(GetProcessHeap(), 0, newGIT);
    }
    else
      TRACE("Created the GIT at %p\n", newGIT);
  }

  return std_git;
}