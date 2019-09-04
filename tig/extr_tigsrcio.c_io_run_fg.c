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
 int /*<<< orphan*/  IO_FG ; 
 int io_complete (int /*<<< orphan*/ ,char const**,char const*,int) ; 

bool
io_run_fg(const char **argv, const char *dir)
{
	return io_complete(IO_FG, argv, dir, -1);
}