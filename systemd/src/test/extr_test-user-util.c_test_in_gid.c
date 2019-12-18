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
 int /*<<< orphan*/  GID_INVALID ; 
 int /*<<< orphan*/  TTY_GID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  getgid () ; 
 scalar_t__ in_gid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_in_gid(void) {

        assert(in_gid(getgid()) >= 0);
        assert(in_gid(getegid()) >= 0);

        assert(in_gid(GID_INVALID) < 0);
        assert(in_gid(TTY_GID) == 0); /* The TTY gid is for owning ttys, it would be really really weird if we were in it. */
}