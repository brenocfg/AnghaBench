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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * last_path_component (char*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_last_path_component(void) {
        assert_se(last_path_component(NULL) == NULL);
        assert_se(streq(last_path_component("a/b/c"), "c"));
        assert_se(streq(last_path_component("a/b/c/"), "c/"));
        assert_se(streq(last_path_component("/"), "/"));
        assert_se(streq(last_path_component("//"), "/"));
        assert_se(streq(last_path_component("///"), "/"));
        assert_se(streq(last_path_component("."), "."));
        assert_se(streq(last_path_component("./."), "."));
        assert_se(streq(last_path_component("././"), "./"));
        assert_se(streq(last_path_component("././/"), ".//"));
        assert_se(streq(last_path_component("/foo/a"), "a"));
        assert_se(streq(last_path_component("/foo/a/"), "a/"));
        assert_se(streq(last_path_component(""), ""));
        assert_se(streq(last_path_component("a"), "a"));
        assert_se(streq(last_path_component("a/"), "a/"));
        assert_se(streq(last_path_component("/a"), "a"));
        assert_se(streq(last_path_component("/a/"), "a/"));
}