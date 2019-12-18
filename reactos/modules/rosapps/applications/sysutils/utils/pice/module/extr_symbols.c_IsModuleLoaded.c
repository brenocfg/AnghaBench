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
struct TYPE_5__ {int /*<<< orphan*/  name; scalar_t__ size; struct TYPE_5__* next; } ;
typedef  TYPE_1__* PDEBUG_MODULE ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 scalar_t__ BuildModuleList () ; 
 int /*<<< orphan*/  CopyWideToAnsi (char*,int /*<<< orphan*/ ) ; 
 int DEBUG_MODULE_NAME_LEN ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ PICE_strcmpi (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pdebug_module_head ; 
 TYPE_1__* pdebug_module_tail ; 

PDEBUG_MODULE IsModuleLoaded(LPSTR p)
{
    PDEBUG_MODULE pd;

	ENTER_FUNC();
	DPRINT((0,"IsModuleLoaded(%s)\n",p));

    if(BuildModuleList())
    {
        pd = pdebug_module_head;
        do
        {
			char temp[DEBUG_MODULE_NAME_LEN];
            DPRINT((0,"module (%x) %S\n",pd->size,pd->name));
			CopyWideToAnsi(temp,pd->name);
            if(pd->size && PICE_strcmpi(p,temp) == 0)
            {
                DPRINT((0,"module %S is loaded!\n",pd->name));
				LEAVE_FUNC();
				return pd;
            }
        }while((pd = pd->next)!=pdebug_module_tail);
    }
	LEAVE_FUNC();
    return NULL;
}