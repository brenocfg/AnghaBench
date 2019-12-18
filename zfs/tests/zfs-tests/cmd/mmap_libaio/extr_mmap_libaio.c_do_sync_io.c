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
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
struct iocb {int dummy; } ;
struct io_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  io_ctx ; 
 int io_getevents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct io_event*,struct timespec*) ; 
 int io_submit (int /*<<< orphan*/ ,int,struct iocb**) ; 

__attribute__((used)) static void
do_sync_io(struct iocb *iocb)
{
	struct io_event event;
	struct iocb *iocbs[] = { iocb };
	struct timespec ts = { 30, 0 };

	if (io_submit(io_ctx, 1, iocbs) != 1)
		err(1, "io_submit failed");

	if (io_getevents(io_ctx, 0, 1, &event, &ts) != 1)
		err(1, "io_getevents failed");
}