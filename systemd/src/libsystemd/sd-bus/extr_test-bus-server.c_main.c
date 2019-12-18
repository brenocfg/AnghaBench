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
 int EPERM ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int test_one (int,int,int,int) ; 

int main(int argc, char *argv[]) {
        int r;

        r = test_one(true, true, false, false);
        assert_se(r >= 0);

        r = test_one(true, false, false, false);
        assert_se(r >= 0);

        r = test_one(false, true, false, false);
        assert_se(r >= 0);

        r = test_one(false, false, false, false);
        assert_se(r >= 0);

        r = test_one(true, true, true, true);
        assert_se(r >= 0);

        r = test_one(true, true, false, true);
        assert_se(r >= 0);

        r = test_one(true, true, true, false);
        assert_se(r == -EPERM);

        return EXIT_SUCCESS;
}