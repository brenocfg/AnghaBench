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
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
struct io {scalar_t__ pipe; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

bool
io_can_read(struct io *io, bool can_block)
{
	struct timeval tv = { 0, 500 };
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(io->pipe, &fds);

	return select(io->pipe + 1, &fds, NULL, NULL, can_block ? NULL : &tv) > 0;
}