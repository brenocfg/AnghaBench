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
struct netnames {int /*<<< orphan*/  type; int /*<<< orphan*/  bcma_core; } ;
typedef  struct netnames sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NET_BCMA ; 
 int /*<<< orphan*/  assert (struct netnames*) ; 
 int sd_device_get_parent_with_subsystem_devtype (struct netnames*,char*,int /*<<< orphan*/ *,struct netnames**) ; 
 int sd_device_get_sysname (struct netnames*,char const**) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  xsprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int names_bcma(sd_device *dev, struct netnames *names) {
        sd_device *bcmadev;
        unsigned core;
        const char *sysname;
        int r;

        assert(dev);
        assert(names);

        r = sd_device_get_parent_with_subsystem_devtype(dev, "bcma", NULL, &bcmadev);
        if (r < 0)
                return r;

        r = sd_device_get_sysname(bcmadev, &sysname);
        if (r < 0)
                return r;

        /* bus num:core num */
        if (sscanf(sysname, "bcma%*u:%u", &core) != 1)
                return -EINVAL;
        /* suppress the common core == 0 */
        if (core > 0)
                xsprintf(names->bcma_core, "b%u", core);

        names->type = NET_BCMA;
        return 0;
}