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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTTY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_syntax (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void test_log_syntax(void) {
        assert_se(log_syntax("unit", LOG_ERR, "filename", 10, EINVAL, "EINVAL: %s: %m", "hogehoge") == -EINVAL);
        assert_se(log_syntax("unit", LOG_ERR, "filename", 10, -ENOENT, "ENOENT: %s: %m", "hogehoge") == -ENOENT);
        assert_se(log_syntax("unit", LOG_ERR, "filename", 10, SYNTHETIC_ERRNO(ENOTTY), "ENOTTY: %s: %m", "hogehoge") == -ENOTTY);
}