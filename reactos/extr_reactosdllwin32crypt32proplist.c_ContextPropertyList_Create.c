#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* DebugInfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  properties; TYPE_3__ cs; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_2__ CONTEXT_PROPERTY_LIST ;

/* Variables and functions */
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_3__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

CONTEXT_PROPERTY_LIST *ContextPropertyList_Create(void)
{
    CONTEXT_PROPERTY_LIST *list = CryptMemAlloc(sizeof(CONTEXT_PROPERTY_LIST));

    if (list)
    {
        InitializeCriticalSection(&list->cs);
        list->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PCONTEXT_PROPERTY_LIST->cs");
        list_init(&list->properties);
    }
    return list;
}