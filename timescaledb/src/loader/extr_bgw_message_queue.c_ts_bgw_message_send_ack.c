#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_4__ {int /*<<< orphan*/  sender_pid; int /*<<< orphan*/  ack_dsm_handle; } ;
typedef  size_t MessageAckSent ;
typedef  TYPE_1__ BgwMessage ;

/* Variables and functions */
 size_t ACK_SENT ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * message_ack_sent_err ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 size_t send_ack (int /*<<< orphan*/ *,int) ; 

extern void
ts_bgw_message_send_ack(BgwMessage *message, bool success)
{
	dsm_segment *seg;

	/*
	 * PG 9.6 does not check to see if we had a CurrentResourceOwner inside of
	 * dsm.c->dsm_create_descriptor.  Basically, it assumed we were in a
	 * transaction if we ever attached to the dsm, whereas PG 10 addressed
	 * that and did proper NULL checking. So, if we are in 9.6, we start a
	 * transaction and then commit it at the end of ack sending, to be sure
	 * everything is cleaned up properly etc.
	 */
#if PG96
	StartTransactionCommand();
#endif
	seg = dsm_attach(message->ack_dsm_handle);
	if (seg != NULL)
	{
		MessageAckSent ack_res;

		ack_res = send_ack(seg, success);
		if (ack_res != ACK_SENT)
			ereport(DEBUG1,
					(errmsg("TimescaleDB background worker launcher unable to send ack to backend "
							"pid %d",
							message->sender_pid),
					 errhint("Reason: %s", message_ack_sent_err[ack_res])));
		dsm_detach(seg);
	}
#if PG96
	CommitTransactionCommand();
#endif
	pfree(message);
}