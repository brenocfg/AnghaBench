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
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int streq (char const*,char*) ; 

__attribute__((used)) static bool is_pci_ari_enabled(sd_device *dev) {
        const char *a;

        if (sd_device_get_sysattr_value(dev, "ari_enabled", &a) < 0)
                return false;

        return streq(a, "1");
}