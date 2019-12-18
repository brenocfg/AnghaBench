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
struct udev_hwdb {int /*<<< orphan*/  properties_list; int /*<<< orphan*/  hwdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udev_hwdb*) ; 
 struct udev_hwdb* mfree (struct udev_hwdb*) ; 
 int /*<<< orphan*/  sd_hwdb_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_list_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct udev_hwdb *udev_hwdb_free(struct udev_hwdb *hwdb) {
        assert(hwdb);

        sd_hwdb_unref(hwdb->hwdb);
        udev_list_free(hwdb->properties_list);
        return mfree(hwdb);
}