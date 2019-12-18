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
struct udev_list {int /*<<< orphan*/  unique_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 struct udev_list* mfree (struct udev_list*) ; 
 int /*<<< orphan*/  udev_list_cleanup (struct udev_list*) ; 

struct udev_list *udev_list_free(struct udev_list *list) {
        if (!list)
                return NULL;

        udev_list_cleanup(list);
        hashmap_free(list->unique_entries);

        return mfree(list);
}