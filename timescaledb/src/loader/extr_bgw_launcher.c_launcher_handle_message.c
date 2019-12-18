#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VirtualTransactionId ;
struct TYPE_7__ {int message_type; int /*<<< orphan*/  sender_pid; } ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ BgwMessage ;
typedef  int /*<<< orphan*/  AckResult ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_FAILURE ; 
 int /*<<< orphan*/ * BackendPidGetProc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_VXID_FROM_PGPROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
#define  RESTART 130 
#define  START 129 
#define  STOP 128 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  message_restart_action (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_start_action (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  message_stop_action (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ts_bgw_message_receive () ; 
 int /*<<< orphan*/  ts_bgw_message_send_ack (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
launcher_handle_message(HTAB *db_htab)
{
	BgwMessage *message = ts_bgw_message_receive();
	PGPROC *sender;
	VirtualTransactionId vxid;
	AckResult action_result = ACK_FAILURE;

	if (message == NULL)
		return false;

	sender = BackendPidGetProc(message->sender_pid);
	if (sender == NULL)
	{
		ereport(LOG,
				(errmsg("TimescaleDB background worker launcher received message from non-existent "
						"backend")));
		return true;
	}

	GET_VXID_FROM_PGPROC(vxid, *sender);

	switch (message->message_type)
	{
		case START:
			action_result = message_start_action(db_htab, message);
			break;
		case STOP:
			action_result = message_stop_action(db_htab, message);
			break;
		case RESTART:
			action_result = message_restart_action(db_htab, message, vxid);
			break;
	}

	ts_bgw_message_send_ack(message, action_result);
	return true;
}