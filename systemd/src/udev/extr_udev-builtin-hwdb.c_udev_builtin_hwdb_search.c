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
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 char* modalias_usb (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ streq (char const*,char const*) ; 
 int udev_builtin_hwdb_lookup (int /*<<< orphan*/ *,char const*,char const*,char const*,int) ; 

__attribute__((used)) static int udev_builtin_hwdb_search(sd_device *dev, sd_device *srcdev,
                                    const char *subsystem, const char *prefix,
                                    const char *filter, bool test) {
        sd_device *d;
        char s[16];
        bool last = false;
        int r = 0;

        assert(dev);

        if (!srcdev)
                srcdev = dev;

        for (d = srcdev; d; ) {
                const char *dsubsys, *devtype, *modalias = NULL;

                if (sd_device_get_subsystem(d, &dsubsys) < 0)
                        goto next;

                /* look only at devices of a specific subsystem */
                if (subsystem && !streq(dsubsys, subsystem))
                        goto next;

                (void) sd_device_get_property_value(d, "MODALIAS", &modalias);

                if (streq(dsubsys, "usb") &&
                    sd_device_get_devtype(d, &devtype) >= 0 &&
                    streq(devtype, "usb_device")) {
                        /* if the usb_device does not have a modalias, compose one */
                        if (!modalias)
                                modalias = modalias_usb(d, s, sizeof(s));

                        /* avoid looking at any parent device, they are usually just a USB hub */
                        last = true;
                }

                if (!modalias)
                        goto next;

                r = udev_builtin_hwdb_lookup(dev, prefix, modalias, filter, test);
                if (r > 0)
                        break;

                if (last)
                        break;
next:
                if (sd_device_get_parent(d, &d) < 0)
                        break;
        }

        return r;
}