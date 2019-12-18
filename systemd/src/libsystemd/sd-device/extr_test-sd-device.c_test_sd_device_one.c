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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  sd_device ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 scalar_t__ IN_SET (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ major (int /*<<< orphan*/ ) ; 
 int sd_device_get_devname (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_devnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_device_get_devpath (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_driver (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_ifindex (int /*<<< orphan*/ *,int*) ; 
 int sd_device_get_is_initialized (int /*<<< orphan*/ *) ; 
 int sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_sysnum (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_usec_since_initialized (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  strna (char const*) ; 
 int /*<<< orphan*/  yes_no (int) ; 

__attribute__((used)) static void test_sd_device_one(sd_device *d) {
        const char *syspath, *subsystem, *val;
        dev_t devnum;
        usec_t usec;
        int i, r;

        assert_se(sd_device_get_syspath(d, &syspath) >= 0);

        r = sd_device_get_subsystem(d, &subsystem);
        assert_se(r >= 0 || r == -ENOENT);

        r = sd_device_get_devtype(d, &val);
        assert_se(r >= 0 || r == -ENOENT);

        r = sd_device_get_devnum(d, &devnum);
        assert_se((r >= 0 && major(devnum) > 0) || r == -ENOENT);

        r = sd_device_get_ifindex(d, &i);
        assert_se((r >= 0 && i > 0) || r == -ENOENT);

        r = sd_device_get_driver(d, &val);
        assert_se(r >= 0 || r == -ENOENT);

        assert_se(sd_device_get_devpath(d, &val) >= 0);

        r = sd_device_get_devname(d, &val);
        assert_se(r >= 0 || r == -ENOENT);

        assert_se(sd_device_get_sysname(d, &val) >= 0);

        r = sd_device_get_sysnum(d, &val);
        assert_se(r >= 0 || r == -ENOENT);

        i = sd_device_get_is_initialized(d);
        assert_se(i >= 0);
        if (i > 0) {
                r = sd_device_get_usec_since_initialized(d, &usec);
                assert_se((r >= 0 && usec > 0) || r == -ENODATA);
        }

        r = sd_device_get_sysattr_value(d, "name_assign_type", &val);
        assert_se(r >= 0 || IN_SET(r, -ENOENT, -EINVAL));

        r = sd_device_get_property_value(d, "ID_NET_DRIVER", &val);
        assert_se(r >= 0 || r == -ENOENT);

        log_info("syspath:%s subsystem:%s initialized:%s", syspath, strna(subsystem), yes_no(i));
}