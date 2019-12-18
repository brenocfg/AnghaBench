#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  devlinks; int /*<<< orphan*/  tags; int /*<<< orphan*/  sysattrs; int /*<<< orphan*/  sysattr_values; int /*<<< orphan*/  properties_db; int /*<<< orphan*/  properties; int /*<<< orphan*/  properties_nulstr; int /*<<< orphan*/  properties_strv; int /*<<< orphan*/  id_filename; int /*<<< orphan*/  driver; int /*<<< orphan*/  driver_subsystem; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  devname; int /*<<< orphan*/  devtype; int /*<<< orphan*/  sysname; int /*<<< orphan*/  syspath; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_free_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ordered_hashmap_free_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_device *device_free(sd_device *device) {
        assert(device);

        sd_device_unref(device->parent);
        free(device->syspath);
        free(device->sysname);
        free(device->devtype);
        free(device->devname);
        free(device->subsystem);
        free(device->driver_subsystem);
        free(device->driver);
        free(device->id_filename);
        free(device->properties_strv);
        free(device->properties_nulstr);

        ordered_hashmap_free_free_free(device->properties);
        ordered_hashmap_free_free_free(device->properties_db);
        hashmap_free_free_free(device->sysattr_values);
        set_free_free(device->sysattrs);
        set_free_free(device->tags);
        set_free_free(device->devlinks);

        return mfree(device);
}