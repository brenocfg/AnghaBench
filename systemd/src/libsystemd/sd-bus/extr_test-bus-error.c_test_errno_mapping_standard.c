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
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EUCLEAN ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  sd_bus_error_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_errno_mapping_standard(void) {
        assert_se(sd_bus_error_set(NULL, "System.Error.EUCLEAN", NULL) == -EUCLEAN);
        assert_se(sd_bus_error_set(NULL, "System.Error.EBUSY", NULL) == -EBUSY);
        assert_se(sd_bus_error_set(NULL, "System.Error.EINVAL", NULL) == -EINVAL);
        assert_se(sd_bus_error_set(NULL, "System.Error.WHATSIT", NULL) == -EIO);
}