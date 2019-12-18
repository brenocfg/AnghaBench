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
typedef  enum io_type { ____Placeholder_io_type } io_type ;

/* Variables and functions */
 scalar_t__ io_done (struct io*) ; 
 scalar_t__ io_exec (struct io*,int,char const*,int /*<<< orphan*/ *,char const**,int) ; 

bool
io_complete(enum io_type type, const char **argv, const char *dir, int fd)
{
	struct io io;

	return io_exec(&io, type, dir, NULL, argv, fd) && io_done(&io);
}