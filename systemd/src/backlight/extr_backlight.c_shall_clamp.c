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
 int /*<<< orphan*/  log_device_debug_errno (int /*<<< orphan*/ *,int,char*) ; 
 int parse_boolean (char const*) ; 
 int sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static bool shall_clamp(sd_device *d) {
        const char *s;
        int r;

        assert(d);

        r = sd_device_get_property_value(d, "ID_BACKLIGHT_CLAMP", &s);
        if (r < 0) {
                log_device_debug_errno(d, r, "Failed to get ID_BACKLIGHT_CLAMP property, ignoring: %m");
                return true;
        }

        r = parse_boolean(s);
        if (r < 0) {
                log_device_debug_errno(d, r, "Failed to parse ID_BACKLIGHT_CLAMP property, ignoring: %m");
                return true;
        }

        return r;
}