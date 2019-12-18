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
 int io_exec (struct io*,int,char const*,char* const*,char const**,int /*<<< orphan*/ ) ; 

bool
io_run(struct io *io, enum io_type type, const char *dir, char * const env[], const char *argv[])
{
	return io_exec(io, type, dir, env, argv, 0);
}