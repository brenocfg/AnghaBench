#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* buffer; } ;
struct TYPE_9__ {TYPE_1__* joliet_name; TYPE_1__* next_in_memory; } ;
struct TYPE_8__ {struct TYPE_8__* joliet_name; struct TYPE_8__* next_in_memory; struct TYPE_8__* entry_list; struct TYPE_8__* next_entry; struct TYPE_8__* next_header; } ;
typedef  TYPE_1__* PDIR_RECORD ;
typedef  TYPE_1__* PBOOT_HEADER ;
typedef  TYPE_1__* PBOOT_ENTRY ;

/* Variables and functions */
 TYPE_1__* boot_header_list ; 
 TYPE_6__ cd ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ joliet ; 
 TYPE_4__ root ; 

__attribute__((used)) static void release_memory(void)
{
    while (boot_header_list)
    {
        PBOOT_HEADER next_header = boot_header_list->next_header;

        while (boot_header_list->entry_list)
        {
            PBOOT_ENTRY next_entry = boot_header_list->entry_list->next_entry;
            free(boot_header_list->entry_list);
            boot_header_list->entry_list = next_entry;
        }

        free(boot_header_list);
        boot_header_list = next_header;
    }

    while (root.next_in_memory != NULL)
    {
        PDIR_RECORD next = root.next_in_memory->next_in_memory;
        if (joliet)
            free(root.next_in_memory->joliet_name);
        free(root.next_in_memory);
        root.next_in_memory = next;
    }
    if (joliet)
        free(root.joliet_name);

    if (cd.buffer != NULL)
    {
        free(cd.buffer);
        cd.buffer = NULL;
    }
}