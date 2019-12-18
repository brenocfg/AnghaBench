#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  db_oid; } ;
struct TYPE_7__ {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ DbHashEntry ;
typedef  TYPE_2__ BgwMessage ;
typedef  int /*<<< orphan*/  AckResult ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_FAILURE ; 
 int /*<<< orphan*/  ACK_SUCCESS ; 
 scalar_t__ DISABLED ; 
 scalar_t__ STARTED ; 
 TYPE_1__* db_hash_entry_create_if_not_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduler_state_trans_automatic (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_state_trans_disabled_to_enabled (TYPE_1__*) ; 

__attribute__((used)) static AckResult
message_start_action(HTAB *db_htab, BgwMessage *message)
{
	DbHashEntry *entry;

	entry = db_hash_entry_create_if_not_exists(db_htab, message->db_oid);

	if (entry->state == DISABLED)
		scheduler_state_trans_disabled_to_enabled(entry);

	scheduler_state_trans_automatic(entry);

	return (entry->state == STARTED ? ACK_SUCCESS : ACK_FAILURE);
}