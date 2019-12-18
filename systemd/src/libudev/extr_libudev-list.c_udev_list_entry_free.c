#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udev_list_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  name; TYPE_1__* list; } ;
struct TYPE_2__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  unique_entries; scalar_t__ unique; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udev_list_entry*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udev_list_entry* mfree (struct udev_list_entry*) ; 

__attribute__((used)) static struct udev_list_entry *udev_list_entry_free(struct udev_list_entry *entry) {
        if (!entry)
                return NULL;

        if (entry->list) {
                if (entry->list->unique)
                        hashmap_remove(entry->list->unique_entries, entry->name);
                else
                        LIST_REMOVE(entries, entry->list->entries, entry);
        }

        free(entry->name);
        free(entry->value);

        return mfree(entry);
}