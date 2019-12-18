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
struct TYPE_7__ {struct TYPE_7__* Next; } ;
typedef  TYPE_1__* PSINGLE_LIST_ENTRY ;
typedef  int /*<<< orphan*/  PKSPIN_LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  PushEntryList (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

PSINGLE_LIST_ENTRY PushEntryListWrapper(PSINGLE_LIST_ENTRY ListHead, PSINGLE_LIST_ENTRY Entry, PKSPIN_LOCK Lock)
{
    PSINGLE_LIST_ENTRY Ret;
    UNREFERENCED_PARAMETER(Lock);
    Ret = ListHead->Next;
    PushEntryList(ListHead, Entry);
    return Ret;
}