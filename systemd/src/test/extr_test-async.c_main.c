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
 int /*<<< orphan*/  async_func ; 
 int /*<<< orphan*/  asynchronous_close (int) ; 
 scalar_t__ asynchronous_job (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ asynchronous_sync (int /*<<< orphan*/ *) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int mkostemp_safe (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int test_async ; 
 int /*<<< orphan*/  unlink (char*) ; 

int main(int argc, char *argv[]) {
        int fd;
        char name[] = "/tmp/test-asynchronous_close.XXXXXX";

        fd = mkostemp_safe(name);
        assert_se(fd >= 0);
        asynchronous_close(fd);

        assert_se(asynchronous_job(async_func, NULL) >= 0);

        assert_se(asynchronous_sync(NULL) >= 0);

        sleep(1);

        assert_se(fcntl(fd, F_GETFD) == -1);
        assert_se(test_async);

        (void) unlink(name);

        return 0;
}