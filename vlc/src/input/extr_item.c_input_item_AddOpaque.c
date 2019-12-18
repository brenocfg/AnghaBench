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
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_2__* opaques; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_6__ {struct TYPE_6__* next; void* value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ input_item_opaque_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int input_item_AddOpaque(input_item_t *item, const char *name, void *value)
{
    assert(name != NULL);

    size_t namelen = strlen(name);
    input_item_opaque_t *entry = malloc(sizeof (*entry) + namelen);
    if (unlikely(entry == NULL))
        return VLC_ENOMEM;

    memcpy(entry->name, name, namelen + 1);
    entry->value = value;

    vlc_mutex_lock(&item->lock);
    entry->next = item->opaques;
    item->opaques = entry;
    vlc_mutex_unlock(&item->lock);
    return VLC_SUCCESS;
}