#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ scan_list_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  scan_list_entry_Delete (TYPE_1__*) ; 

void scan_list_entries_release( scan_list_entry_t *p_list )
{
    while( p_list )
    {
        scan_list_entry_t *p_next = p_list->p_next;
        scan_list_entry_Delete( p_list );
        p_list = p_next;
    }
}