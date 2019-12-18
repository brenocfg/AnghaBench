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
struct netnames {int /*<<< orphan*/ * mac; int /*<<< orphan*/  mac_valid; } ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  udev_builtin_hwdb_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xsprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee_oui(sd_device *dev, struct netnames *names, bool test) {
        char str[32];

        if (!names->mac_valid)
                return -ENOENT;
        /* skip commonly misused 00:00:00 (Xerox) prefix */
        if (memcmp(names->mac, "\0\0\0", 3) == 0)
                return -EINVAL;
        xsprintf(str, "OUI:%02X%02X%02X%02X%02X%02X", names->mac[0],
                 names->mac[1], names->mac[2], names->mac[3], names->mac[4],
                 names->mac[5]);
        udev_builtin_hwdb_lookup(dev, NULL, str, NULL, test);
        return 0;
}