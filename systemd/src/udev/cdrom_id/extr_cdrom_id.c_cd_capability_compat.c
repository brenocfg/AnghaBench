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
 int CDC_CD_R ; 
 int CDC_CD_RW ; 
 int CDC_DVD ; 
 int CDC_DVD_R ; 
 int CDC_DVD_RAM ; 
 int CDC_MRW ; 
 int CDC_MRW_W ; 
 int /*<<< orphan*/  CDROM_GET_CAPABILITY ; 
 int cd_cd_r ; 
 int cd_cd_rw ; 
 int cd_dvd_r ; 
 int cd_dvd_ram ; 
 int cd_dvd_rom ; 
 int cd_mrw ; 
 int cd_mrw_w ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cd_capability_compat(int fd) {
        int capability;

        capability = ioctl(fd, CDROM_GET_CAPABILITY, NULL);
        if (capability < 0)
                return log_debug_errno(errno, "CDROM_GET_CAPABILITY failed");

        if (capability & CDC_CD_R)
                cd_cd_r = 1;
        if (capability & CDC_CD_RW)
                cd_cd_rw = 1;
        if (capability & CDC_DVD)
                cd_dvd_rom = 1;
        if (capability & CDC_DVD_R)
                cd_dvd_r = 1;
        if (capability & CDC_DVD_RAM)
                cd_dvd_ram = 1;
        if (capability & CDC_MRW)
                cd_mrw = 1;
        if (capability & CDC_MRW_W)
                cd_mrw_w = 1;
        return 0;
}