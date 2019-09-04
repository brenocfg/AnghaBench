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
struct TYPE_4__ {scalar_t__ state_transition_failures; int /*<<< orphan*/  vxid; int /*<<< orphan*/  state; int /*<<< orphan*/ * db_scheduler_handle; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ DbHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLED ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  SetInvalidVirtualTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scheduler_state_trans_enabled_to_allocated (TYPE_1__*) ; 

__attribute__((used)) static DbHashEntry *
db_hash_entry_create_if_not_exists(HTAB *db_htab, Oid db_oid)
{
	DbHashEntry *db_he;
	bool found;

	db_he = (DbHashEntry *) hash_search(db_htab, &db_oid, HASH_ENTER, &found);
	if (!found)
	{
		db_he->db_scheduler_handle = NULL;
		db_he->state = ENABLED;
		SetInvalidVirtualTransactionId(db_he->vxid);
		db_he->state_transition_failures = 0;

		/*
		 * Try to allocate a spot right away to give schedulers priority over
		 * other bgws. This is especially important on initial server startup
		 * where we want to reserve slots for all schedulers before starting
		 * any. This is done so that background workers started by schedulers
		 * don't race for open slots with other schedulers on startup.
		 */
		scheduler_state_trans_enabled_to_allocated(db_he);
	}

	return db_he;
}