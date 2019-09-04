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
struct TYPE_6__ {int NumberOfNamedEntries; int NumberOfIdEntries; } ;
struct TYPE_5__ {int OffsetToDirectory; int /*<<< orphan*/  DataIsDirectory; } ;
typedef  TYPE_1__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_2__ IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */

IMAGE_RESOURCE_DIRECTORY *find_first_entry( IMAGE_RESOURCE_DIRECTORY *dir,
                                            void *root, int want_dir )
{
    const IMAGE_RESOURCE_DIRECTORY_ENTRY *entry = (const IMAGE_RESOURCE_DIRECTORY_ENTRY *)(dir + 1);
    int pos;

    for (pos = 0; pos < dir->NumberOfNamedEntries + dir->NumberOfIdEntries; pos++)
    {
        if (!entry[pos].DataIsDirectory == !want_dir)
            return (IMAGE_RESOURCE_DIRECTORY *)((char *)root + entry[pos].OffsetToDirectory);
    }
    return NULL;
}