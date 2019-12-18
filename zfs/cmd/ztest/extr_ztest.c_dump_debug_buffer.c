#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  zo_dump_dbgmsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zfs_dbgmsg_print (char*) ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static void
dump_debug_buffer(void)
{
	ssize_t ret __attribute__((unused));

	if (!ztest_opts.zo_dump_dbgmsg)
		return;

	/*
	 * We use write() instead of printf() so that this function
	 * is safe to call from a signal handler.
	 */
	ret = write(STDOUT_FILENO, "\n", 1);
	zfs_dbgmsg_print("ztest");
}