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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int state; scalar_t__ writes; scalar_t__ reads; scalar_t__ nwritten; scalar_t__ nread; scalar_t__ ndirty; scalar_t__* times; scalar_t__ txg; } ;
typedef  TYPE_1__ spa_txg_history_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
#define  TXG_STATE_BIRTH 133 
#define  TXG_STATE_COMMITTED 132 
#define  TXG_STATE_OPEN 131 
#define  TXG_STATE_QUIESCED 130 
#define  TXG_STATE_SYNCED 129 
#define  TXG_STATE_WAIT_FOR_SYNC 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,scalar_t__,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_txg_history_show(struct seq_file *f, void *data)
{
	spa_txg_history_t *sth = (spa_txg_history_t *)data;
	uint64_t open = 0, quiesce = 0, wait = 0, sync = 0;
	char state;

	switch (sth->state) {
		case TXG_STATE_BIRTH:		state = 'B';	break;
		case TXG_STATE_OPEN:		state = 'O';	break;
		case TXG_STATE_QUIESCED:	state = 'Q';	break;
		case TXG_STATE_WAIT_FOR_SYNC:	state = 'W';	break;
		case TXG_STATE_SYNCED:		state = 'S';	break;
		case TXG_STATE_COMMITTED:	state = 'C';	break;
		default:			state = '?';	break;
	}

	if (sth->times[TXG_STATE_OPEN])
		open = sth->times[TXG_STATE_OPEN] -
		    sth->times[TXG_STATE_BIRTH];

	if (sth->times[TXG_STATE_QUIESCED])
		quiesce = sth->times[TXG_STATE_QUIESCED] -
		    sth->times[TXG_STATE_OPEN];

	if (sth->times[TXG_STATE_WAIT_FOR_SYNC])
		wait = sth->times[TXG_STATE_WAIT_FOR_SYNC] -
		    sth->times[TXG_STATE_QUIESCED];

	if (sth->times[TXG_STATE_SYNCED])
		sync = sth->times[TXG_STATE_SYNCED] -
		    sth->times[TXG_STATE_WAIT_FOR_SYNC];

	seq_printf(f, "%-8llu %-16llu %-5c %-12llu "
	    "%-12llu %-12llu %-8llu %-8llu %-12llu %-12llu %-12llu %-12llu\n",
	    (longlong_t)sth->txg, sth->times[TXG_STATE_BIRTH], state,
	    (u_longlong_t)sth->ndirty,
	    (u_longlong_t)sth->nread, (u_longlong_t)sth->nwritten,
	    (u_longlong_t)sth->reads, (u_longlong_t)sth->writes,
	    (u_longlong_t)open, (u_longlong_t)quiesce, (u_longlong_t)wait,
	    (u_longlong_t)sync);

	return (0);
}