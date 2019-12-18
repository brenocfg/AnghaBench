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
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  PTR_TO_FD (void*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  close_nointr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setname_np (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *close_thread(void *p) {
        (void) pthread_setname_np(pthread_self(), "close");

        assert_se(close_nointr(PTR_TO_FD(p)) != -EBADF);
        return NULL;
}