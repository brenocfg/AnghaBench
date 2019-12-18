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
 int /*<<< orphan*/  CAT_FLAGS_MAIN_FILE_OPTIONAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/ * STRV_MAKE (char*,char*) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  cat_files (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_cat_files(void) {
        assert_se(cat_files("/no/such/file", NULL, 0) == -ENOENT);
        assert_se(cat_files("/no/such/file", NULL, CAT_FLAGS_MAIN_FILE_OPTIONAL) == 0);

        if (access("/etc/fstab", R_OK) >= 0)
                assert_se(cat_files("/etc/fstab", STRV_MAKE("/etc/fstab", "/etc/fstab"), 0) == 0);
}