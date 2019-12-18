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
 char* SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  test_slice_to_path_one (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_slice_to_path(void) {
        test_slice_to_path_one("foobar.slice", "foobar.slice", 0);
        test_slice_to_path_one("foobar-waldo.slice", "foobar.slice/foobar-waldo.slice", 0);
        test_slice_to_path_one("foobar-waldo.service", NULL, -EINVAL);
        test_slice_to_path_one(SPECIAL_ROOT_SLICE, "", 0);
        test_slice_to_path_one("--.slice", NULL, -EINVAL);
        test_slice_to_path_one("-", NULL, -EINVAL);
        test_slice_to_path_one("-foo-.slice", NULL, -EINVAL);
        test_slice_to_path_one("-foo.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo-.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo--bar.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo.slice/foo--bar.slice", NULL, -EINVAL);
        test_slice_to_path_one("a-b.slice", "a.slice/a-b.slice", 0);
        test_slice_to_path_one("a-b-c-d-e.slice", "a.slice/a-b.slice/a-b-c.slice/a-b-c-d.slice/a-b-c-d-e.slice", 0);

        test_slice_to_path_one("foobar@.slice", NULL, -EINVAL);
        test_slice_to_path_one("foobar@waldo.slice", NULL, -EINVAL);
        test_slice_to_path_one("foobar@waldo.service", NULL, -EINVAL);
        test_slice_to_path_one("-foo@-.slice", NULL, -EINVAL);
        test_slice_to_path_one("-foo@.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo@-.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo@@bar.slice", NULL, -EINVAL);
        test_slice_to_path_one("foo.slice/foo@@bar.slice", NULL, -EINVAL);
}