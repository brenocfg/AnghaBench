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
struct io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 scalar_t__ io_read_buf (struct io*,char*,size_t,int) ; 
 scalar_t__ io_run (struct io*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const**) ; 

bool
io_run_buf(const char **argv, char buf[], size_t bufsize, const char *dir, bool allow_empty)
{
	struct io io;

	return io_run(&io, IO_RD, dir, NULL, argv) && io_read_buf(&io, buf, bufsize, allow_empty);
}