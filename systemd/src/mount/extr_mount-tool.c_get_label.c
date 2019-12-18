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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static const char* get_label(sd_device *d) {
        const char *label;

        assert(d);

        if (sd_device_get_property_value(d, "ID_FS_LABEL", &label) >= 0)
                return label;

        if (sd_device_get_property_value(d, "ID_PART_ENTRY_NAME", &label) >= 0)
                return label;

        return NULL;
}