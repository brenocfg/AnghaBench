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
struct io {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 

bool
io_kill(struct io *io)
{
	return io->pid == 0 || kill(io->pid, SIGKILL) != -1;
}