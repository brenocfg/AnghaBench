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
typedef  int /*<<< orphan*/  bitmask_rel ;
typedef  int /*<<< orphan*/  bitmask_props ;
typedef  int /*<<< orphan*/  bitmask_key ;
typedef  int /*<<< orphan*/  bitmask_ev ;
typedef  int /*<<< orphan*/  bitmask_abs ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MAX ; 
 int /*<<< orphan*/  EV_MAX ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  INPUT_PROP_MAX ; 
 int /*<<< orphan*/  KEY_MAX ; 
 int NBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_MAX ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_info (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  get_cap_mask (int /*<<< orphan*/ *,char*,unsigned long*,int,int) ; 
 scalar_t__ sd_device_get_devname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_parent_with_subsystem_devtype (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ startswith (char const*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int test_key (int /*<<< orphan*/ *,unsigned long*,unsigned long*,int) ; 
 int test_pointers (int /*<<< orphan*/ *,unsigned long*,unsigned long*,unsigned long*,unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  udev_builtin_add_property (int /*<<< orphan*/ *,int,char*,char*) ; 

__attribute__((used)) static int builtin_input_id(sd_device *dev, int argc, char *argv[], bool test) {
        sd_device *pdev;
        unsigned long bitmask_ev[NBITS(EV_MAX)];
        unsigned long bitmask_abs[NBITS(ABS_MAX)];
        unsigned long bitmask_key[NBITS(KEY_MAX)];
        unsigned long bitmask_rel[NBITS(REL_MAX)];
        unsigned long bitmask_props[NBITS(INPUT_PROP_MAX)];
        const char *sysname, *devnode;
        bool is_pointer;
        bool is_key;

        assert(dev);

        /* walk up the parental chain until we find the real input device; the
         * argument is very likely a subdevice of this, like eventN */
        for (pdev = dev; pdev; ) {
                const char *s;

                if (sd_device_get_sysattr_value(pdev, "capabilities/ev", &s) >= 0)
                        break;

                if (sd_device_get_parent_with_subsystem_devtype(pdev, "input", NULL, &pdev) >= 0)
                        continue;

                pdev = NULL;
                break;
        }

        if (pdev) {
                /* Use this as a flag that input devices were detected, so that this
                 * program doesn't need to be called more than once per device */
                udev_builtin_add_property(dev, test, "ID_INPUT", "1");
                get_cap_mask(pdev, "capabilities/ev", bitmask_ev, sizeof(bitmask_ev), test);
                get_cap_mask(pdev, "capabilities/abs", bitmask_abs, sizeof(bitmask_abs), test);
                get_cap_mask(pdev, "capabilities/rel", bitmask_rel, sizeof(bitmask_rel), test);
                get_cap_mask(pdev, "capabilities/key", bitmask_key, sizeof(bitmask_key), test);
                get_cap_mask(pdev, "properties", bitmask_props, sizeof(bitmask_props), test);
                is_pointer = test_pointers(dev, bitmask_ev, bitmask_abs,
                                           bitmask_key, bitmask_rel,
                                           bitmask_props, test);
                is_key = test_key(dev, bitmask_ev, bitmask_key, test);
                /* Some evdev nodes have only a scrollwheel */
                if (!is_pointer && !is_key && test_bit(EV_REL, bitmask_ev) &&
                    (test_bit(REL_WHEEL, bitmask_rel) || test_bit(REL_HWHEEL, bitmask_rel)))
                        udev_builtin_add_property(dev, test, "ID_INPUT_KEY", "1");
                if (test_bit(EV_SW, bitmask_ev))
                        udev_builtin_add_property(dev, test, "ID_INPUT_SWITCH", "1");

        }

        if (sd_device_get_devname(dev, &devnode) >= 0 &&
            sd_device_get_sysname(dev, &sysname) >= 0 &&
            startswith(sysname, "event"))
                extract_info(dev, devnode, test);

        return 0;
}