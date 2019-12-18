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
 int /*<<< orphan*/  CDROM_DRIVE_STATUS ; 
 int /*<<< orphan*/  CDSL_CURRENT ; 
 scalar_t__ CDS_DISC_OK ; 
 int cd_media ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cd_media_compat(int fd) {
        if (ioctl(fd, CDROM_DRIVE_STATUS, CDSL_CURRENT) != CDS_DISC_OK)
                return log_debug_errno(errno, "CDROM_DRIVE_STATUS != CDS_DISC_OK");

        cd_media = 1;
        return 0;
}