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
struct app_external {int /*<<< orphan*/  argv; int /*<<< orphan*/  env; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 scalar_t__ io_read_buf (struct io*,char*,size_t,int) ; 
 scalar_t__ io_run (struct io*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
app_oneline_buf(char *buf, size_t bufsize, struct app_external *app, const char *dir)
{
	struct io io;
	return io_run(&io, IO_RD, dir, app->env, app->argv) \
		&& io_read_buf(&io, buf, bufsize, false);
}