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
 void* ENOMEM ; 
 scalar_t__ broken (int) ; 
 void* calloc (size_t,size_t) ; 
 void* errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ok (int,char*,void*) ; 

__attribute__((used)) static void test_calloc(void)
{
    void *ptr;

    ptr = calloc(1, 0);
    ok(ptr != NULL, "got %p\n", ptr);
    free(ptr);

    ptr = calloc(0, 0);
    ok(ptr != NULL, "got %p\n", ptr);
    free(ptr);

    ptr = calloc(0, 1);
    ok(ptr != NULL, "got %p\n", ptr);
    free(ptr);

    errno = 0;
    ptr = calloc(~(size_t)0 / 2, ~(size_t)0 / 2);
    ok(ptr == NULL || broken(ptr != NULL) /* winxp sp0 */, "got %p\n", ptr);
    ok(errno == ENOMEM || broken(errno == 0) /* winxp, win2k3 */, "got errno %d\n", errno);
    free(ptr);
}