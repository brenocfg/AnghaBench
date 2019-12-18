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
typedef  int /*<<< orphan*/  sd_device_enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int enumerator_scan_dir (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_debug_errno (int,char*) ; 

__attribute__((used)) static int enumerator_scan_devices_all(sd_device_enumerator *enumerator) {
        int r = 0;

        log_debug("sd-device-enumerator: Scan all dirs");

        if (access("/sys/subsystem", F_OK) >= 0) {
                /* we have /subsystem/, forget all the old stuff */
                r = enumerator_scan_dir(enumerator, "subsystem", "devices", NULL);
                if (r < 0)
                        return log_debug_errno(r, "sd-device-enumerator: Failed to scan /sys/subsystem: %m");
        } else {
                int k;

                k = enumerator_scan_dir(enumerator, "bus", "devices", NULL);
                if (k < 0) {
                        log_debug_errno(k, "sd-device-enumerator: Failed to scan /sys/bus: %m");
                        r = k;
                }

                k = enumerator_scan_dir(enumerator, "class", NULL, NULL);
                if (k < 0) {
                        log_debug_errno(k, "sd-device-enumerator: Failed to scan /sys/class: %m");
                        r = k;
                }
        }

        return r;
}