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

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int VIRTUALIZATION_NONE ; 
 int VIRTUALIZATION_XEN ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int detect_vm_xen(void) {

        /* Check for Dom0 will be executed later in detect_vm_xen_dom0
           The presence of /proc/xen indicates some form of a Xen domain */
        if (access("/proc/xen", F_OK) < 0) {
                log_debug("Virtualization XEN not found, /proc/xen does not exist");
                return VIRTUALIZATION_NONE;
        }

        log_debug("Virtualization XEN found (/proc/xen exists)");
        return VIRTUALIZATION_XEN;
}