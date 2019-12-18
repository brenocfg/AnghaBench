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
 char* arphrd_to_name (unsigned short) ; 
 int /*<<< orphan*/  ascii_strlower (char*) ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 scalar_t__ sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *link_get_type_string(unsigned short iftype, sd_device *d) {
        const char *t, *devtype;
        char *p;

        if (d &&
            sd_device_get_devtype(d, &devtype) >= 0 &&
            !isempty(devtype))
                return strdup(devtype);

        t = arphrd_to_name(iftype);
        if (!t)
                return NULL;

        p = strdup(t);
        if (!p)
                return NULL;

        ascii_strlower(p);
        return p;
}