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
 int device_add_property_aux (int /*<<< orphan*/ *,char const*,char const*,int) ; 

int device_add_property_internal(sd_device *device, const char *key, const char *value) {
        return device_add_property_aux(device, key, value, false);
}