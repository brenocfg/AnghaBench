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
typedef  char const sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int device_add_property_aux (char const*,char const*,char const*,int) ; 

int device_add_property(sd_device *device, const char *key, const char *value) {
        int r;

        assert(device);
        assert(key);

        r = device_add_property_aux(device, key, value, false);
        if (r < 0)
                return r;

        if (key[0] != '.') {
                r = device_add_property_aux(device, key, value, true);
                if (r < 0)
                        return r;
        }

        return 0;
}