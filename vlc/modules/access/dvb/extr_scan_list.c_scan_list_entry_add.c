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
struct TYPE_6__ {struct TYPE_6__* p_next; } ;
typedef  TYPE_1__ scan_list_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  scan_list_entry_Delete (TYPE_1__*) ; 
 scalar_t__ scan_list_entry_validate (TYPE_1__*) ; 

__attribute__((used)) static bool scan_list_entry_add( scan_list_entry_t ***ppp_last, scan_list_entry_t *p_entry )
{
    if( scan_list_entry_validate( p_entry ) )
    {
         **ppp_last = p_entry;
         *ppp_last = &p_entry->p_next;
        return true;
    }

    scan_list_entry_Delete( p_entry );
    return false;
}