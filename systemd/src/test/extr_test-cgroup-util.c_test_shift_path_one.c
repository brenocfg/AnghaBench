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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ cg_shift_path (char const*,char const*,char const**) ; 
 int streq (char const*,char const*) ; 

__attribute__((used)) static void test_shift_path_one(const char *raw, const char *root, const char *shifted) {
        const char *s = NULL;

        assert_se(cg_shift_path(raw, root, &s) >= 0);
        assert_se(streq(s, shifted));
}