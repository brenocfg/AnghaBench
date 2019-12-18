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
struct tmuxproc {int /*<<< orphan*/  name; int /*<<< orphan*/  exit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOOP_ONCE ; 
 int /*<<< orphan*/  event_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 

void
proc_loop(struct tmuxproc *tp, int (*loopcb)(void))
{
	log_debug("%s loop enter", tp->name);
	do
		event_loop(EVLOOP_ONCE);
	while (!tp->exit && (loopcb == NULL || !loopcb ()));
	log_debug("%s loop exit", tp->name);
}