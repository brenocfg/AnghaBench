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
 char* BUS_ERROR_NO_SUCH_UNIT ; 
 int /*<<< orphan*/  EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  sd_bus_error_add_map (int /*<<< orphan*/ ) ; 
 int sd_bus_error_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_errors3 ; 
 int /*<<< orphan*/  test_errors4 ; 
 int /*<<< orphan*/  test_errors_bad1 ; 
 int /*<<< orphan*/  test_errors_bad2 ; 

__attribute__((used)) static void test_errno_mapping_custom(void) {
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error", NULL) == -5);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-2", NULL) == -52);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-x", NULL) == -EIO);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-33", NULL) == -333);

        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-88", NULL) == -EIO);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-99", NULL) == -EIO);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-77", NULL) == -EIO);

        assert_se(sd_bus_error_add_map(test_errors3) > 0);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-88", NULL) == -888);
        assert_se(sd_bus_error_add_map(test_errors4) > 0);
        assert_se(sd_bus_error_add_map(test_errors4) == 0);
        assert_se(sd_bus_error_add_map(test_errors3) == 0);

        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-99", NULL) == -999);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-77", NULL) == -777);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-78", NULL) == -778);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-2", NULL) == -52);
        assert_se(sd_bus_error_set(NULL, "org.freedesktop.custom-dbus-error-y", NULL) == -EIO);

        assert_se(sd_bus_error_set(NULL, BUS_ERROR_NO_SUCH_UNIT, NULL) == -ENOENT);

        assert_se(sd_bus_error_add_map(test_errors_bad1) == -EINVAL);
        assert_se(sd_bus_error_add_map(test_errors_bad2) == -EINVAL);
}