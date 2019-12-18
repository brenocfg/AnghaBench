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
typedef  int /*<<< orphan*/ **** sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITS ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  STARTSWITH_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ******) ; 
 int log_warning_errno (int,char*,char const*,char const*,char const*) ; 
 int safe_atolu (char const*,unsigned long*) ; 
 int sd_device_get_parent (int /*<<< orphan*/ *****,int /*<<< orphan*/ ******) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *****,char const**) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *****,char*,char const**) ; 
 int sd_device_get_sysname (int /*<<< orphan*/ *****,char const**) ; 
 char* startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_pci_or_platform_parent(sd_device *device, sd_device **ret) {
        const char *subsystem, *sysname, *value;
        sd_device *parent;
        int r;

        assert(device);
        assert(ret);

        r = sd_device_get_parent(device, &parent);
        if (r < 0)
                return r;

        r = sd_device_get_subsystem(parent, &subsystem);
        if (r < 0)
                return r;

        r = sd_device_get_sysname(parent, &sysname);
        if (r < 0)
                return r;

        if (streq(subsystem, "drm")) {
                const char *c;

                c = startswith(sysname, "card");
                if (!c)
                        return -ENODATA;

                c += strspn(c, DIGITS);
                if (*c == '-') {
                        /* A connector DRM device, let's ignore all but LVDS and eDP! */
                        if (!STARTSWITH_SET(c, "-LVDS-", "-Embedded DisplayPort-"))
                                return -EOPNOTSUPP;
                }

        } else if (streq(subsystem, "pci") &&
                   sd_device_get_sysattr_value(parent, "class", &value) >= 0) {
                unsigned long class = 0;

                r = safe_atolu(value, &class);
                if (r < 0)
                        return log_warning_errno(r, "Cannot parse PCI class '%s' of device %s:%s: %m",
                                                 value, subsystem, sysname);

                /* Graphics card */
                if (class == 0x30000) {
                        *ret = parent;
                        return 0;
                }

        } else if (streq(subsystem, "platform")) {
                *ret = parent;
                return 0;
        }

        return find_pci_or_platform_parent(parent, ret);
}