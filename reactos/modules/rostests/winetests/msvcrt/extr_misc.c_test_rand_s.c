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
 int EBADF ; 
 int EINVAL ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int prand_s (unsigned int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_rand_s(void)
{
    int ret;
    unsigned int rand;

    if (!prand_s)
    {
        win_skip("rand_s is not available\n");
        return;
    }

    errno = EBADF;
    ret = prand_s(NULL);
    ok(ret == EINVAL, "Expected rand_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to return EINVAL, got %d\n", errno);

    ret = prand_s(&rand);
    ok(ret == 0, "Expected rand_s to return 0, got %d\n", ret);
}