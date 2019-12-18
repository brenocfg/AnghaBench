#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct guidsection_header {int index_offset; scalar_t__ count; } ;
struct guid_index {int /*<<< orphan*/  guid; } ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct guid_index *find_guid_index(const struct guidsection_header *section, const GUID *guid)
{
    struct guid_index *iter, *index = NULL;
    ULONG i;

    iter = (struct guid_index*)((BYTE*)section + section->index_offset);

    for (i = 0; i < section->count; i++)
    {
        if (!memcmp(guid, &iter->guid, sizeof(*guid)))
        {
            index = iter;
            break;
        }
        iter++;
    }

    return index;
}