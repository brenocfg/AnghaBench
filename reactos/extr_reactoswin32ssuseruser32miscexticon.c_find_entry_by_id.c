#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_6__ {int NumberOfNamedEntries; int NumberOfIdEntries; } ;
struct TYPE_5__ {scalar_t__ Id; int OffsetToDirectory; } ;
typedef  TYPE_1__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_2__ IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */

__attribute__((used)) static const IMAGE_RESOURCE_DIRECTORY *find_entry_by_id( const IMAGE_RESOURCE_DIRECTORY *dir,
                                                         WORD id, const void *root )
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
            return (const IMAGE_RESOURCE_DIRECTORY *)((const char *)root + entry[pos].OffsetToDirectory);
        if (entry[pos].Id > id) max = pos - 1;
        else min = pos + 1;
    }
    return NULL;
}