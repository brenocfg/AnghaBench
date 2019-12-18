#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  name; scalar_t__ BaseAddress; struct TYPE_5__* next; } ;
typedef  TYPE_1__* PDEBUG_MODULE ;

/* Variables and functions */
 scalar_t__ BuildModuleList () ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 TYPE_1__* pdebug_module_head ; 
 TYPE_1__* pdebug_module_tail ; 

PDEBUG_MODULE FindModuleFromAddress(ULONG addr)
{
    PDEBUG_MODULE pd;
    ULONG start,end;

    DPRINT((0,"FindModuleFromAddress()\n"));
    if(BuildModuleList())
    {
        pd = pdebug_module_head;
        do
        {
			if(pd->size)
			{
                start = (ULONG)pd->BaseAddress;
                end = start + pd->size;
                DPRINT((0,"FindModuleFromAddress(): %S %x-%x\n",pd->name,start,end));
                if(addr>=start && addr<end)
                {
                    DPRINT((0,"FindModuleFromAddress(): found %S\n",pd->name));
                    return pd;
                }
            }
        }while((pd = pd->next)!=pdebug_module_tail);
    }

    return NULL;
}