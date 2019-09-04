#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_7__ {int NumberOfNamedEntries; int NumberOfIdEntries; } ;
struct TYPE_6__ {scalar_t__ Id; int OffsetToDirectory; int /*<<< orphan*/  DataIsDirectory; } ;
typedef  TYPE_1__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_2__ IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,void*,TYPE_2__*,scalar_t__,...) ; 

IMAGE_RESOURCE_DIRECTORY *find_entry_by_id( IMAGE_RESOURCE_DIRECTORY *dir,
                                            WORD id, void *root, int want_dir )
{
    const IMAGE_RESOURCE_DIRECTORY_ENTRY *entry;
    int min, max, pos;

    entry = (const IMAGE_RESOURCE_DIRECTORY_ENTRY *)(dir + 1);
    min = dir->NumberOfNamedEntries;
    max = min + dir->NumberOfIdEntries - 1;
    while (min <= max)
    {
        pos = (min + max) / 2;
        if (entry[pos].Id == id)
        {
            if (!entry[pos].DataIsDirectory == !want_dir)
            {
                DPRINT("root %p dir %p id %04x ret %p\n",
                       root, dir, id, (const char*)root + entry[pos].OffsetToDirectory);
                return (IMAGE_RESOURCE_DIRECTORY *)((char *)root + entry[pos].OffsetToDirectory);
            }
            break;
        }
        if (entry[pos].Id > id) max = pos - 1;
        else min = pos + 1;
    }
    DPRINT("root %p dir %p id %04x not found\n", root, dir, id );
    return NULL;
}