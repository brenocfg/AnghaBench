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
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  close_many (int*,int) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int mkostemp_safe (char*) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_close_many(void) {
        int fds[3];
        char name0[] = "/tmp/test-close-many.XXXXXX";
        char name1[] = "/tmp/test-close-many.XXXXXX";
        char name2[] = "/tmp/test-close-many.XXXXXX";

        fds[0] = mkostemp_safe(name0);
        fds[1] = mkostemp_safe(name1);
        fds[2] = mkostemp_safe(name2);

        close_many(fds, 2);

        assert_se(fcntl(fds[0], F_GETFD) == -1);
        assert_se(fcntl(fds[1], F_GETFD) == -1);
        assert_se(fcntl(fds[2], F_GETFD) >= 0);

        safe_close(fds[2]);

        unlink(name0);
        unlink(name1);
        unlink(name2);
}