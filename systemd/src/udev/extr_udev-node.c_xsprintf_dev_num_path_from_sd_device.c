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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int DEV_NUM_PATH_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char**) ; 
 int sd_device_get_devnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 char* strdup (char*) ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  xsprintf_dev_num_path (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsprintf_dev_num_path_from_sd_device(sd_device *dev, char **ret) {
        char filename[DEV_NUM_PATH_MAX], *s;
        const char *subsystem;
        dev_t devnum;
        int r;

        assert(ret);

        r = sd_device_get_subsystem(dev, &subsystem);
        if (r < 0)
                return r;

        r = sd_device_get_devnum(dev, &devnum);
        if (r < 0)
                return r;

        xsprintf_dev_num_path(filename,
                              streq(subsystem, "block") ? "block" : "char",
                              devnum);

        s = strdup(filename);
        if (!s)
                return -ENOMEM;

        *ret = s;
        return 0;
}