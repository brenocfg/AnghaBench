#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VirtualTransactionId ;
struct TYPE_9__ {int /*<<< orphan*/  db_oid; } ;
struct TYPE_8__ {int state; int /*<<< orphan*/  db_scheduler_handle; int /*<<< orphan*/  vxid; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ DbHashEntry ;
typedef  TYPE_2__ BgwMessage ;
typedef  int /*<<< orphan*/  AckResult ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_FAILURE ; 
 int /*<<< orphan*/  ACK_SUCCESS ; 
#define  ALLOCATED 131 
#define  DISABLED 130 
#define  ENABLED 129 
#define  STARTED 128 
 TYPE_1__* db_hash_entry_create_if_not_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduler_state_trans_automatic (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_state_trans_disabled_to_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_state_trans_started_to_allocated (TYPE_1__*) ; 
 int /*<<< orphan*/  terminate_background_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_background_worker_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static AckResult
message_restart_action(HTAB *db_htab, BgwMessage *message, VirtualTransactionId vxid)
{
	DbHashEntry *entry;

	entry = db_hash_entry_create_if_not_exists(db_htab, message->db_oid);

	entry->vxid = vxid;

	switch (entry->state)
	{
		case ENABLED:
			break;
		case ALLOCATED:
			break;
		case STARTED:
			terminate_background_worker(entry->db_scheduler_handle);
			wait_for_background_worker_shutdown(entry->db_scheduler_handle);
			scheduler_state_trans_started_to_allocated(entry);
			break;
		case DISABLED:
			scheduler_state_trans_disabled_to_enabled(entry);
	}

	scheduler_state_trans_automatic(entry);
	return entry->state == STARTED ? ACK_SUCCESS : ACK_FAILURE;
}