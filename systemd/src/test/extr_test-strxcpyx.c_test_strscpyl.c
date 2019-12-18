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
typedef  int /*<<< orphan*/  target ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int streq (char*,char*) ; 
 size_t strscpyl (char*,size_t,char*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_strscpyl(void) {
        char target[25];
        size_t space_left;

        space_left = sizeof(target);
        space_left = strscpyl(target, space_left, "12345", "waldo", "waldo", NULL);

        assert_se(streq(target, "12345waldowaldo"));
        assert_se(space_left == 10);
}