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
 int CDO_LOCK ; 
 int /*<<< orphan*/  CDROM_CLEAR_OPTIONS ; 
 int /*<<< orphan*/  CDROM_LOCKDOOR ; 
 int ioctl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int media_lock(int fd, bool lock) {
        int err;

        /* disable the kernel's lock logic */
        err = ioctl(fd, CDROM_CLEAR_OPTIONS, CDO_LOCK);
        if (err < 0)
                log_debug("CDROM_CLEAR_OPTIONS, CDO_LOCK failed");

        err = ioctl(fd, CDROM_LOCKDOOR, lock ? 1 : 0);
        if (err < 0)
                log_debug("CDROM_LOCKDOOR failed");

        return err;
}