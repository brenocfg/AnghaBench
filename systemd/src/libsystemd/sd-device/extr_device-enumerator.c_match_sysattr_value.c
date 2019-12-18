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
 scalar_t__ fnmatch (char const*,char const*,int /*<<< orphan*/ ) ; 
 int sd_device_get_sysattr_value (char const*,char const*,char const**) ; 

__attribute__((used)) static bool match_sysattr_value(sd_device *device, const char *sysattr, const char *match_value) {
        const char *value;
        int r;

        assert(device);
        assert(sysattr);

        r = sd_device_get_sysattr_value(device, sysattr, &value);
        if (r < 0)
                return false;

        if (!match_value)
                return true;

        if (fnmatch(match_value, value, 0) == 0)
                return true;

        return false;
}