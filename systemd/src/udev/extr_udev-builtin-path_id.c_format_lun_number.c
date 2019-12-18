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
 int ENOENT ; 
 int /*<<< orphan*/  path_prepend (char**,char*,unsigned long,...) ; 
 int sd_device_get_sysnum (int /*<<< orphan*/ *,char const**) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int format_lun_number(sd_device *dev, char **path) {
        const char *sysnum;
        unsigned long lun;
        int r;

        r = sd_device_get_sysnum(dev, &sysnum);
        if (r < 0)
                return r;
        if (!sysnum)
                return -ENOENT;

        lun = strtoul(sysnum, NULL, 10);
        if (lun < 256)
                /* address method 0, peripheral device addressing with bus id of zero */
                path_prepend(path, "lun-%lu", lun);
        else
                /* handle all other lun addressing methods by using a variant of the original lun format */
                path_prepend(path, "lun-0x%04lx%04lx00000000", lun & 0xffff, (lun >> 16) & 0xffff);

        return 0;
}